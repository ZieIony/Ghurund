#include "GPUBuffer.h"

namespace Ghurund {
    void GPUBuffer::set(Graphics& graphics, CommandList& commandList, unsigned int bindSlot) {
        ID3D12Resource* constantBufferUploadHeap = nullptr; // this is the memory on the gpu where our constant buffer will be placed.
        Pointer* resourcePointer = graphics.ResourceFactory.create(D3D12_HEAP_TYPE_UPLOAD, CD3DX12_RESOURCE_DESC::Buffer(align<size_t>(buffer->Size, 1024 * 64)), D3D12_RESOURCE_STATE_GENERIC_READ, &constantBufferUploadHeap);

#ifdef _DEBUG
        if (resourcePointer == nullptr) {
            Logger::log(LogType::ERR0R, _T("unable to create a resource\n"));
            return;
        }
#endif

        CD3DX12_RANGE readRange(0, 0);
        constantBufferUploadHeap->Map(0, &readRange, (void**)& gpuAddress);

        memcpy(gpuAddress, buffer->Data, buffer->Size);
        CD3DX12_RANGE writeRange(0, buffer->Size);
        constantBufferUploadHeap->Unmap(0, &writeRange);

        commandList.get()->SetGraphicsRootConstantBufferView(bindSlot, constantBufferUploadHeap->GetGPUVirtualAddress());
        commandList.addPointerRef(resourcePointer);
        resourcePointer->release();
    }
}