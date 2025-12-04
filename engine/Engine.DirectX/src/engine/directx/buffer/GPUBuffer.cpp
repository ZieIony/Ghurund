#include "ghedxpch.h"
#include "GPUBuffer.h"

#include "core/logging/Logger.h"
#include "engine/directx/DxGraphics.h"

namespace Ghurund::Engine::DirectX {
    void GPUBuffer::init(DxGraphics& graphics, size_t size) {
        resourcePointer = graphics.ResourceFactory.create(D3D12_HEAP_TYPE_UPLOAD, CD3DX12_RESOURCE_DESC::Buffer(align<size_t>(size, 64_KB)), D3D12_RESOURCE_STATE_GENERIC_READ, &constantBufferUploadHeap);

#ifdef _DEBUG
        if (resourcePointer == nullptr) {
            Logger::log(LogType::ERR0R, _T("unable to create a resource\n"));
            return;
        }
#endif

        buffer = ghnew Buffer(size);
    }

    void GPUBuffer::uninit() {
        // constantBufferUploadHeap and resourcePointer are basically the same resource in the same memory block
        if (constantBufferUploadHeap) {
            constantBufferUploadHeap->Release();
            constantBufferUploadHeap = nullptr;
        }
        if (resourcePointer) {
            resourcePointer->release();
            resourcePointer = nullptr;
        }
        delete buffer;
    }

    void GPUBuffer::set(CommandList & commandList, unsigned int bindSlot) {
        CD3DX12_RANGE readRange(0, 0);
        constantBufferUploadHeap->Map(0, &readRange, (void**)& gpuAddress);

        memcpy(gpuAddress, buffer->Data, buffer->Size);
        CD3DX12_RANGE writeRange(0, buffer->Size);
        constantBufferUploadHeap->Unmap(0, &writeRange);

        commandList.get()->SetGraphicsRootConstantBufferView(bindSlot, constantBufferUploadHeap->GetGPUVirtualAddress());
        commandList.addPointerRef(resourcePointer);
    }
}