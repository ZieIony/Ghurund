#include "GPUBuffer.h"

namespace Ghurund {
    void GPUBuffer::set(Graphics& graphics, CommandList& commandList, unsigned int bindSlot) {
        ID3D12Resource* constantBufferUploadHeap = nullptr; // this is the memory on the gpu where our constant buffer will be placed.
        Pointer* resourcePointer = graphics.ResourceFactory.create(D3D12_HEAP_TYPE_UPLOAD, CD3DX12_RESOURCE_DESC::Buffer(align<unsigned int>(buffer->Size, 1024 * 64)), D3D12_RESOURCE_STATE_GENERIC_READ, &constantBufferUploadHeap);

#ifdef _DEBUG
        if (resourcePointer == nullptr) {
            Logger::log(LogType::ERR0R, _T("unable to create a resource\n"));
            return;
        }
#endif

        D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
        cbvDesc.BufferLocation = constantBufferUploadHeap->GetGPUVirtualAddress();
        cbvDesc.SizeInBytes = align<unsigned int>(buffer->Size, 256);    // CB size is required to be 256-byte aligned.
        graphics.Device->CreateConstantBufferView(&cbvDesc, descHandle.getCpuHandle());

        CD3DX12_RANGE readRange(0, 0);
        constantBufferUploadHeap->Map(0, &readRange, (void**)& gpuAddress);

        memcpy(gpuAddress, buffer->Data, buffer->Size);

        commandList.get()->SetGraphicsRootDescriptorTable(bindSlot, descHandle.getGpuHandle());
        commandList.addPointerRef(resourcePointer);
        resourcePointer->release();
    }
}