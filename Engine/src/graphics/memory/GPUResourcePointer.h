#pragma once

#include "core/collection/Map.h"
#include "core/Pointer.h"
#include "HeapAllocator.h"

#pragma warning(push, 0)
#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include "d3dx12.h"
#pragma warning(pop)

#include <wrl.h>

namespace Ghurund {
    class GPUResourcePointer:public Pointer {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(GPUResourcePointer);
  
        HeapAllocator* allocator;
        void* address;
        ID3D12Resource *resource;

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

		inline static const Ghurund::Type& TYPE = TypeBuilder<GPUResourcePointer>(NAMESPACE_NAME, CLASS_NAME)
            .withSupertype(Pointer::TYPE);

        virtual const Ghurund::Type&getType() const override {
            return TYPE;
        }
    };
}