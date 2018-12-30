#pragma once

#include "collection/Map.h"
#include "core/Allocator.h"
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
        AllocationStrategy *strategy;

    public:
        HeapAllocator(Graphics &graphics, memory_t size, AllocationStrategy *strategy, D3D12_HEAP_TYPE type, D3D12_HEAP_FLAGS flags);

        ~HeapAllocator() {
            if(heap!=nullptr)
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
    };

    class GPUResourcePointer:public Pointer {
    private:
        HeapAllocator *allocator;
        memory_t address;
        ID3D12Resource *resource;

    public:
        GPUResourcePointer(HeapAllocator *allocator, memory_t address, ID3D12Resource *resource){
            this->allocator = allocator;
            this->address = address;
            this->resource = resource;
        }

        ~GPUResourcePointer() {
            resource->Release();
            allocator->deallocate(address);
        }

        virtual const Ghurund::Type &getType() const override {
            return Type::MESH;
        }
    };

    class GPUResourceFactory {
    private:
        Graphics &graphics;
        Map<D3D12_HEAP_TYPE, HeapAllocator*> allocators;
        D3D12_CLEAR_VALUE depthClearValue = {};

    public:
        GPUResourceFactory(Graphics &graphics);

        ~GPUResourceFactory() {
            delete allocators.getValue(0);
            delete allocators.getValue(1);
        }

        GPUResourcePointer *create(D3D12_HEAP_TYPE heapType, CD3DX12_RESOURCE_DESC resourceDesc, D3D12_RESOURCE_STATES initialState, ID3D12Resource **resource);
    };
}