#include "ghpch.h"
#include "Texture.h"

#include "core/io/File.h"
#include "core/io/MemoryStream.h"

namespace Ghurund {
	Status Texture::loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
        /*Status result;
        image = (Ghurund::Image*)context.ResourceManager.load(context, workingDir, stream, &result, options);
        if (filterStatus(result, options) != Status::OK)
            return result;
        return init(context, *image);*/
        return Status::NOT_IMPLEMENTED;
    }

    Status Texture::saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
        //return context.ResourceManager.save(*image, context, workingDir, stream, options);
        return Status::NOT_IMPLEMENTED;
    }

    const Ghurund::Type& Texture::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<Texture>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Texture))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    Status Texture::init(Graphics& graphics, CommandList& commandList, Ghurund::Image &image) {
        if(commandList.State==CommandListState::FINISHED)
            commandList.reset();

		descHandle = graphics.DescriptorAllocator.allocate(graphics, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
        setPointer(this->image, &image);

        {
            D3D12_RESOURCE_DESC textureDesc = {};
            textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
            textureDesc.Alignment = 0;  // let the driver choose
            textureDesc.Width = image.Width;
            textureDesc.Height = image.Height;
            textureDesc.DepthOrArraySize = 1;
            textureDesc.MipLevels = 1;
            textureDesc.Format = image.Format;
            textureDesc.SampleDesc.Count = 1;
            textureDesc.SampleDesc.Quality = 0;
            textureDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;  // let the driver choose
            textureDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

            auto defaultHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
            if(FAILED(graphics.getDevice()->CreateCommittedResource(
                &defaultHeapProperties,
                D3D12_HEAP_FLAG_NONE,
                &textureDesc,
                D3D12_RESOURCE_STATE_COPY_DEST,
                nullptr,
                IID_PPV_ARGS(&textureResource)))) {
                return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("graphics->getDevice()->CreateCommittedResource() failed\n"));
            }

            const UINT64 uploadBufferSize = GetRequiredIntermediateSize(textureResource.Get(), 0, 1);

            auto uploadHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
            auto uploadResourceDesc = CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize);
            if(FAILED((graphics.getDevice()->CreateCommittedResource(
                &uploadHeapProperties,
                D3D12_HEAP_FLAG_NONE,
                &uploadResourceDesc,
                D3D12_RESOURCE_STATE_GENERIC_READ,
                nullptr,
                IID_PPV_ARGS(&textureUploadHeap))))) {
                return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("graphics->getDevice()->CreateCommittedResource() failed\n"));
            }

            D3D12_SUBRESOURCE_DATA textureData = {};
            textureData.pData = image.Data.Data;
            textureData.RowPitch = image.Width * image.PixelSize;
            textureData.SlicePitch = textureData.RowPitch * image.Height;

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

        Valid = true;

        return Status::OK;
    }
}