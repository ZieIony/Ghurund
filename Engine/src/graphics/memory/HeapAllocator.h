#pragma once

#include "collection/Map.h"
#include "core/allocation/AllocationStrategy.h"
#include "core/Pointer.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include "d3dx12.h"
#include <wrl.h>

namespace Ghurund {
    class Graphics;

    class HeapAllocator:public Allocator<memory_t> {
    public:
        ID3D12Heap* heap = nullptr;
        AllocationStrategy* strategy;

    public:
        HeapAllocator(Graphics& graphics, memory_t size, AllocationStrategy* strategy, D3D12_HEAP_TYPE type, D3D12_HEAP_FLAGS flags);

        ~HeapAllocator() {
            if (heap != nullptr)
                heap->Release();
            delete strategy;
        }

        inline memory_t allocate(memory_t size) {
            return strategy->allocate(size);
        }

        inline void deallocate(memory_t mem) {
            strategy->deallocate(mem);
        }

        ID3D12Heap* getHeap() {
            return heap;
        }

        __declspec(property(get = getHeap)) ID3D12Heap* Heap;

        memory_t getSize() {
            return strategy->getSize();
        }

        __declspec(property(get = getSize)) memory_t Size;

        memory_t getAllocated() {
            return strategy->getAllocated();
        }

        __declspec(property(get = getAllocated)) memory_t Allocated;
    };

}