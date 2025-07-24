#pragma once

#include "HeapAllocator.h"
#include "core/object/RefCountedObject.h"

#pragma warning(push, 0)
#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#pragma warning(pop)

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class GPUResourcePointer:public RefCountedObject {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = GPUResourcePointer::GET_TYPE();
#pragma endregion

    private:
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
    };
}