#include "ghedxpch.h"
#include "DxTexture.h"

#include "core/logging/Logger.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Engine::DirectX {
    const Ghurund::Core::Type& DxTexture::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<DxTexture>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    DXGI_FORMAT DxTexture::adjustFormat(DXGI_FORMAT format, TextureType textureType) {
        if (textureType == TextureType::OTHER)
            return format;

        if (format >= DXGI_FORMAT_R8G8B8A8_TYPELESS && format <= DXGI_FORMAT_R8G8B8A8_SINT)
            return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
        if (format == DXGI_FORMAT_B8G8R8X8_TYPELESS || format == DXGI_FORMAT_B8G8R8X8_UNORM)
            return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
        if (format == DXGI_FORMAT_B8G8R8A8_TYPELESS || format == DXGI_FORMAT_B8G8R8A8_UNORM)
            return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
        if (format == DXGI_FORMAT_BC1_TYPELESS || format == DXGI_FORMAT_BC1_UNORM)
            return DXGI_FORMAT_BC1_UNORM_SRGB;
        if (format == DXGI_FORMAT_BC2_TYPELESS || format == DXGI_FORMAT_BC2_UNORM)
            return DXGI_FORMAT_BC1_UNORM_SRGB;
        if (format == DXGI_FORMAT_BC3_TYPELESS || format == DXGI_FORMAT_BC3_UNORM)
            return DXGI_FORMAT_BC1_UNORM_SRGB;
        if (format == DXGI_FORMAT_BC7_TYPELESS || format == DXGI_FORMAT_BC7_UNORM)
            return DXGI_FORMAT_BC7_UNORM_SRGB;
        return format;
    }

    void DxTexture::init(
        DxGraphics& graphics,
        CommandList& commandList,
        Ghurund::Core::Image& image,
        TextureType textureType
    ) {
		if (commandList.State == CommandListState::FINISHED)
            commandList.reset();

		descHandle = graphics.DescriptorAllocator.allocate(graphics, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
        setPointer(this->image, &image);

        {
            D3D12_RESOURCE_DESC textureDesc = {};
            textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
            textureDesc.Alignment = 0;  // let the driver choose
            textureDesc.Width = image.Size.Width;
            textureDesc.Height = image.Size.Height;
            textureDesc.DepthOrArraySize = 1;
            textureDesc.MipLevels = 1;
            textureDesc.Format = adjustFormat(image.Format, textureType);
            textureDesc.SampleDesc.Count = 1;
            textureDesc.SampleDesc.Quality = 0;
            textureDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;  // let the driver choose
            textureDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

            auto defaultHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
            if(FAILED(graphics.Device->CreateCommittedResource(
                &defaultHeapProperties,
                D3D12_HEAP_FLAG_NONE,
                &textureDesc,
                D3D12_RESOURCE_STATE_COPY_DEST,
                nullptr,
                IID_PPV_ARGS(&textureResource)))) {
                Logger::log(LogType::ERR0R, _T("graphics->getDevice()->CreateCommittedResource() failed\n"));
                throw CallFailedException();
            }

            const UINT64 uploadBufferSize = GetRequiredIntermediateSize(textureResource.Get(), 0, 1);

            auto uploadHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
            auto uploadResourceDesc = CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize);
            if(FAILED((graphics.Device->CreateCommittedResource(
                &uploadHeapProperties,
                D3D12_HEAP_FLAG_NONE,
                &uploadResourceDesc,
                D3D12_RESOURCE_STATE_GENERIC_READ,
                nullptr,
                IID_PPV_ARGS(&textureUploadHeap))))) {
                Logger::log(LogType::ERR0R, _T("graphics->getDevice()->CreateCommittedResource() failed\n"));
                throw CallFailedException();
            }

            D3D12_SUBRESOURCE_DATA textureData = {};
            textureData.pData = image.Data.Data;
            textureData.RowPitch = image.Size.Width * image.PixelSize;
            textureData.SlicePitch = textureData.RowPitch * image.Size.Height;

            UpdateSubresources(commandList.get(), textureResource.Get(), textureUploadHeap.Get(), 0, 0, 1, &textureData);
            auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(textureResource.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
            commandList.get()->ResourceBarrier(1, &barrier);

            D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
            srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
            srvDesc.Format = textureDesc.Format;
            srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
            srvDesc.Texture2D.MipLevels = 1;
            graphics.Device->CreateShaderResourceView(textureResource.Get(), &srvDesc, descHandle.CpuHandle);
        }

        commandList.addResourceRef(textureResource.Get());
        commandList.finish();
        commandList.wait();

        uploaded = true;
    }
}