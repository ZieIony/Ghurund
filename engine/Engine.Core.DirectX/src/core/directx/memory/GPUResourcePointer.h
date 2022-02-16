#pragma once

#include "HeapAllocator.h"
#include "core/collection/Map.h"
#include "core/Pointer.h"

#pragma warning(push, 0)
#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include "d3dx12.h"
#pragma warning(pop)

namespace Ghurund::Core::DirectX {
    using namespace Ghurund::Core;

    class GPUResourcePointer:public Pointer {
    private:
        HeapAllocator* allocator;
        void* address;
        ID3D12Resource *resource;

    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        GPUResourcePointer(HeapAllocator *allocator, void* address, ID3D12Resource *resource){
            this->allocator = allocator;
            this->address = address;
            this->resource = resource;
        }

        ~GPUResourcePointer() {
            resource->Release();
            allocator->deallocate(address);
        }

        static const Ghurund::Core::Type& GET_TYPE();
    };
}