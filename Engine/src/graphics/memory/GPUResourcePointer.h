#pragma once

#include "collection/Map.h"
#include "core/Pointer.h"
#include "HeapAllocator.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include "d3dx12.h"
#include <wrl.h>

namespace Ghurund {
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
}