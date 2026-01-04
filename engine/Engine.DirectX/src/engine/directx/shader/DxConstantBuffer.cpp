#include "ghedxpch.h"
#include "DxConstantBuffer.h"

#include "core/logging/Logger.h"

#pragma warning(push, 0)
#include <d3dx12.h>
#pragma warning(pop)

namespace Ghurund::Engine::DirectX {
    using namespace ::DirectX;

    void DxConstantBuffer::init(ComPtr<ID3D12Resource> uploadHeap) {
        uploadHeap->AddRef();
        constantBufferUploadHeap = uploadHeap.Get();

        buffer = ghnew Buffer(uploadHeap->GetDesc().Width);
    }

    void DxConstantBuffer::uninit() {
        // constantBufferUploadHeap and resourcePointer are basically the same resource in the same memory block
        if (constantBufferUploadHeap) {
            constantBufferUploadHeap->Release();
            constantBufferUploadHeap = nullptr;
        }
        delete buffer;
        buffer = nullptr;
    }

	void DxConstantBuffer::set(CommandList& commandList, uint32_t bindSlot) {
        CD3DX12_RANGE readRange(0, 0);
        void* gpuAddress = nullptr;
        constantBufferUploadHeap->Map(0, &readRange, (void**)& gpuAddress);

        memcpy(gpuAddress, buffer->Data, buffer->Size);
        CD3DX12_RANGE writeRange(0, buffer->Size);
        constantBufferUploadHeap->Unmap(0, &writeRange);

        commandList.get()->SetGraphicsRootConstantBufferView(bindSlot, constantBufferUploadHeap->GetGPUVirtualAddress());
        commandList.addResourceRef(constantBufferUploadHeap);
    }
}