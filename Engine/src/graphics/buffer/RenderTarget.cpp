#include "RenderTarget.h"

namespace Ghurund {
    Status RenderTarget::init(Graphics& graphics, ID3D12Resource* texture) {
        D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
        rtvHeapDesc.NumDescriptors = 1;
        rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        if (FAILED(graphics.getDevice()->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap))))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("device->CreateDescriptorHeap() failed\n"));

        handle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
        graphics.getDevice()->CreateRenderTargetView(texture, nullptr, handle);
        this->texture = texture;

#ifdef _DEBUG
        rtvHeap->SetName(L"rtvHeap");
        texture->SetName(L"renderTarget");
#endif

        return Status::OK;
    }

    Status RenderTarget::init(Graphics& graphics, unsigned int width, unsigned int height, DXGI_FORMAT format) {
        this->format = format;

        CD3DX12_HEAP_PROPERTIES heapProperty(D3D12_HEAP_TYPE_DEFAULT);

        D3D12_RESOURCE_DESC resourceDesc;
        ZeroMemory(&resourceDesc, sizeof(resourceDesc));
        resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
        resourceDesc.Alignment = 0;
        resourceDesc.SampleDesc.Count = 1;
        resourceDesc.SampleDesc.Quality = 0;
        resourceDesc.MipLevels = 1;

        resourceDesc.DepthOrArraySize = 1;
        resourceDesc.Width = width;
        resourceDesc.Height = height;
        resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
        resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

        D3D12_CLEAR_VALUE clearVal;
        clearVal.Color[0] = 0;
        clearVal.Color[1] = 0;
        clearVal.Color[2] = 0;
        clearVal.Color[3] = 0;

        resourceDesc.Format = format;
        clearVal.Format = format;
        if (FAILED(graphics.Device->CreateCommittedResource(
            &heapProperty, D3D12_HEAP_FLAG_NONE, &resourceDesc, state, &clearVal, IID_PPV_ARGS(&texture)))) {
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("init RenderTarget with internal texture failed\n"));
        }

        return init(graphics, texture);
    }

    void RenderTarget::uninit() {
        if (rtvHeap) {
            rtvHeap->Release();
            rtvHeap = nullptr;
        }
        if (texture) {
            texture->Release();
            texture = nullptr;
        }
    }

    Status RenderTarget::captureTexture(Graphics &graphics, ID3D12CommandQueue* commandQueue, UINT64 srcPitch, const D3D12_RESOURCE_DESC& desc, ComPtr<ID3D12Resource>& stagingTexture) {
        ID3D12Device* device = graphics.Device;

        if (desc.Dimension != D3D12_RESOURCE_DIMENSION_TEXTURE2D) {
            Logger::log(LogType::ERR0R, _T("1D or volume textures are not supported\n"));
            return Status::NOT_SUPPORTED;
        }

        if (desc.DepthOrArraySize > 1 || desc.MipLevels > 1) {
            Logger::log(LogType::ERR0R, _T("2D arrays, cubemaps, or mipmaps are not supported\n"));
            return Status::NOT_SUPPORTED;
        }

        UINT numberOfPlanes = D3D12GetFormatPlaneCount(device, desc.Format);
        if (numberOfPlanes != 1) {
            Logger::log(LogType::ERR0R, _T("more than 1 plane is not supported\n"));
            return Status::NOT_SUPPORTED;
        }

        CommandList *commandList = ghnew CommandList();
        if (commandList->init(graphics, commandQueue) != Status::OK)
            return Status::CALL_FAIL;
        commandList->reset();

        assert((srcPitch & 0xFF) == 0);

        CD3DX12_HEAP_PROPERTIES defaultHeapProperties(D3D12_HEAP_TYPE_DEFAULT);
        CD3DX12_HEAP_PROPERTIES readBackHeapProperties(D3D12_HEAP_TYPE_READBACK);

        D3D12_RESOURCE_DESC bufferDesc = {};
        bufferDesc.Alignment = desc.Alignment;
        bufferDesc.DepthOrArraySize = 1;
        bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        bufferDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
        bufferDesc.Format = DXGI_FORMAT_UNKNOWN;
        bufferDesc.Height = 1;
        bufferDesc.Width = srcPitch * desc.Height;
        bufferDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        bufferDesc.MipLevels = 1;
        bufferDesc.SampleDesc.Count = 1;
        bufferDesc.SampleDesc.Quality = 0;

        ComPtr<ID3D12Resource> copySource(texture);
        if (desc.SampleDesc.Count > 1) {
            // MSAA content must be resolved before being copied to a staging texture
            auto descCopy = desc;
            descCopy.SampleDesc.Count = 1;
            descCopy.SampleDesc.Quality = 0;

            ComPtr<ID3D12Resource> pTemp;
            HRESULT hr = device->CreateCommittedResource(
                &defaultHeapProperties,
                D3D12_HEAP_FLAG_NONE,
                &descCopy,
                D3D12_RESOURCE_STATE_COPY_DEST,
                nullptr,
                IID_PPV_ARGS(pTemp.GetAddressOf()));
            if (FAILED(hr))
                return Status::CALL_FAIL;

            assert(pTemp);

            DXGI_FORMAT fmt = desc.Format;

            D3D12_FEATURE_DATA_FORMAT_SUPPORT formatInfo = {fmt, D3D12_FORMAT_SUPPORT1_NONE, D3D12_FORMAT_SUPPORT2_NONE};
            hr = device->CheckFeatureSupport(D3D12_FEATURE_FORMAT_SUPPORT, &formatInfo, sizeof(formatInfo));
            if (FAILED(hr))
                return Status::CALL_FAIL;

            if (!(formatInfo.Support1 & D3D12_FORMAT_SUPPORT1_TEXTURE2D))
                return Status::CALL_FAIL;

            for (UINT item = 0; item < desc.DepthOrArraySize; ++item) {
                for (UINT level = 0; level < desc.MipLevels; ++level) {
                    UINT index = D3D12CalcSubresource(level, item, 0, desc.MipLevels, desc.DepthOrArraySize);
                    commandList->get()->ResolveSubresource(pTemp.Get(), index, texture, index, fmt);
                }
            }

            copySource = pTemp;
        }

        HRESULT hr = device->CreateCommittedResource(
            &readBackHeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &bufferDesc,
            D3D12_RESOURCE_STATE_COPY_DEST,
            nullptr,
            IID_PPV_ARGS(stagingTexture.ReleaseAndGetAddressOf()));
        if (FAILED(hr))
            return Status::CALL_FAIL;

        commandList->barrier(CD3DX12_RESOURCE_BARRIER::Transition(texture, state, D3D12_RESOURCE_STATE_COPY_SOURCE));

        D3D12_PLACED_SUBRESOURCE_FOOTPRINT bufferFootprint = {};
        bufferFootprint.Footprint.Width = static_cast<UINT>(desc.Width);
        bufferFootprint.Footprint.Height = desc.Height;
        bufferFootprint.Footprint.Depth = 1;
        bufferFootprint.Footprint.RowPitch = static_cast<UINT>(srcPitch);
        bufferFootprint.Footprint.Format = desc.Format;

        CD3DX12_TEXTURE_COPY_LOCATION copyDest(stagingTexture.Get(), bufferFootprint);
        CD3DX12_TEXTURE_COPY_LOCATION copySrc(copySource.Get(), 0);
        commandList->get()->CopyTextureRegion(&copyDest, 0, 0, 0, &copySrc, nullptr);

        commandList->barrier(CD3DX12_RESOURCE_BARRIER::Transition(texture, D3D12_RESOURCE_STATE_COPY_SOURCE, state));

        if (commandList->finish()!=Status::OK)
            return Status::CALL_FAIL;
        commandList->wait();
        commandList->release();

        return Status::OK;
    }

    Status RenderTarget::capture(ResourceContext& context, Image*& image) {
        ID3D12Device* device = context.Graphics.Device;
        IWICImagingFactory* pWIC = context.ImageFactory;
        ID3D12CommandQueue* commandQueue = context.Graphics.DirectQueue;

        const auto desc = texture->GetDesc();

        UINT64 totalResourceSize = 0;
        UINT64 fpRowPitch = 0;
        UINT fpRowCount = 0;
        // Get the rowcount, pitch and size of the top mip
        device->GetCopyableFootprints(&desc, 0, 1, 0, nullptr, &fpRowCount, &fpRowPitch, &totalResourceSize);

        UINT64 dstRowPitch = (fpRowPitch + 255) & ~0xFF;

        ComPtr<ID3D12Resource> stagingTexture;
        Status result = captureTexture(context.Graphics, commandQueue, dstRowPitch, desc, stagingTexture);
        if (result != Status::OK)
            return result;

        UINT64 imageSize = dstRowPitch * UINT64(desc.Height);
        void* mappedMemory = nullptr;
        D3D12_RANGE readRange = {0, static_cast<SIZE_T>(imageSize)};
        D3D12_RANGE writeRange = {0, 0};
        HRESULT hr = stagingTexture->Map(0, &readRange, &mappedMemory);
        if (FAILED(hr))
            return Status::CALL_FAIL;

        Buffer* buffer = ghnew Buffer(mappedMemory, (size_t)imageSize);
        image = ghnew Image(*buffer, (UINT32)desc.Width, (UINT32)desc.Height, desc.Format);
        delete buffer;
        stagingTexture->Unmap(0, &writeRange);

        return Status::OK;
    }
}