#include "ghedxpch.h"
#include "DxObjectParametersBuffer.h"

#pragma warning(push, 0)
#include <d3dx12.h>
#pragma warning(pop)

namespace Ghurund::Engine::DirectX {
    using namespace ::DirectX;

    void DxObjectParametersBuffer::init(ComPtr<ID3D12Resource> uploadHeap) {
        uploadHeap->AddRef();
        resource = uploadHeap.Get();

        buffer = ghnew Buffer(uploadHeap->GetDesc().Width);
    }

    void DxObjectParametersBuffer::deinit() {
        // resource and resourcePointer are basically the same resource in the same memory block
        if (resource) {
            resource->Release();
            resource = nullptr;
        }
        delete buffer;
        buffer = nullptr;
    }

    void DxObjectParametersBuffer::setValue(const ObjectParameters& value, size_t index) {
#ifdef _DEBUG
        _ASSERTE(sizeof(ObjectParameters) * (index + 1) <= buffer->Size);
#endif
        memcpy((uint8_t*)buffer->Data + sizeof(ObjectParameters) * index, &value, sizeof(ObjectParameters));
    }

    void DxObjectParametersBuffer::set(CommandList& commandList, uint32_t bindSlot) {
        CD3DX12_RANGE readRange(0, 0);
        void* gpuAddress = nullptr;
        resource->Map(0, &readRange, (void**)&gpuAddress);

        memcpy(gpuAddress, buffer->Data, buffer->Size);
        CD3DX12_RANGE writeRange(0, buffer->Size);
        resource->Unmap(0, &writeRange);

        commandList.get()->SetGraphicsRootShaderResourceView(bindSlot, resource->GetGPUVirtualAddress());
        commandList.addResourceRef(resource);
    }
}
