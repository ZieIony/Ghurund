#pragma once

#include "collection/Map.h"
#include "core/Allocator.h"
#include "core/Pointer.h"
#include "HeapAllocator.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include "d3dx12.h"
#include <wrl.h>

namespace Ghurund {
    class Graphics;

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

        memory_t getSize() {
            memory_t size = 0;
            for (size_t i = 0; i < allocators.Size; i++)
                size += allocators.getValue(i)->Size;
            return size;
        }

        __declspec(property(get = getSize)) memory_t Size;

        memory_t getAllocated() {
            memory_t allocated = 0;
            for (size_t i = 0; i < allocators.Size; i++)
                allocated += allocators.getValue(i)->Allocated;
            return allocated;
        }

        __declspec(property(get = getAllocated)) memory_t Allocated;

    };
}