#pragma once

#include "core/collection/Map.h"
#include "core/Pointer.h"
#include "HeapAllocator.h"
#include "GPUResourcePointer.h"

#pragma warning(push, 0)
#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include "d3dx12.h"
#pragma warning(pop)

#include <wrl.h>

namespace Ghurund::Core::DirectX {
    class Graphics;

    class GPUResourceFactory {
    private:
        Graphics &graphics;
        Map<D3D12_HEAP_TYPE, HeapAllocator*> allocators;
        D3D12_CLEAR_VALUE depthClearValue = {};

    public:
        GPUResourceFactory(Graphics &graphics);

        ~GPUResourceFactory() {
            for (auto& [heapType, allocator] : allocators)
                delete allocator;
        }

        GPUResourcePointer *create(D3D12_HEAP_TYPE heapType, CD3DX12_RESOURCE_DESC resourceDesc, D3D12_RESOURCE_STATES initialState, ID3D12Resource **resource);

        uint64_t getSize() {
            uint64_t size = 0;
            for (auto& [heapType, allocator] : allocators)
                size += allocator->Size;
            return size;
        }

        __declspec(property(get = getSize)) uint64_t Size;

        uint64_t getAllocated() {
            uint64_t allocated = 0;
            for (auto& [heapType, allocator] : allocators)
                allocated += allocator->Allocated;
            return allocated;
        }

        __declspec(property(get = getAllocated)) uint64_t Allocated;

    };
}