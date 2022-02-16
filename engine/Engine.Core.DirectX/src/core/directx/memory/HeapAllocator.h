#pragma once

#include "core/collection/Map.h"
#include "core/allocation/AllocationStrategy.h"
#include "core/Pointer.h"

#pragma warning(push, 0)
#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include "d3dx12.h"
#pragma warning(pop)

#include <wrl.h>

namespace Ghurund::Core::DirectX {
    using namespace Ghurund::Core;

    class Graphics;

    class HeapAllocator:public Allocator {
    public:
        ID3D12Heap* heap = nullptr;
        AllocationStrategy* strategy;

    public:
        HeapAllocator(Graphics& graphics, uint64_t size, AllocationStrategy* strategy, D3D12_HEAP_TYPE type, D3D12_HEAP_FLAGS flags);

        ~HeapAllocator() {
            if (heap != nullptr)
                heap->Release();
            delete strategy;
        }

        inline void* allocate(uint64_t size) {
            return (void*)strategy->allocate(size);
        }

        inline void deallocate(void* mem) {
            strategy->deallocate((uint64_t)mem);
        }

        ID3D12Heap* getHeap() {
            return heap;
        }

        __declspec(property(get = getHeap)) ID3D12Heap* Heap;

        size_t getSize() {
            return strategy->getSize();
        }

        __declspec(property(get = getSize)) size_t Size;

        size_t getAllocated() {
            return strategy->getAllocated();
        }

        __declspec(property(get = getAllocated)) size_t Allocated;

		inline bool canAllocate(size_t size) const {
			return strategy->canAllocate(size);
		}
    };

}