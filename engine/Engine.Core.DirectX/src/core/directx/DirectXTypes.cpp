#include "ghcdxpch.h"
#include "DirectXTypes.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<ID3D12CommandQueue>() {
        static Type TYPE = Type("", "ID3D12CommandQueue", sizeof(ID3D12CommandQueue));
        return TYPE;
    }

    template<>
    const Type& getType<ID3D12Device>() {
        static Type TYPE = Type("", "ID3D12Device", sizeof(ID3D12Device));
        return TYPE;
    }

    template<>
    const Type& getType<IDXGIFactory4>() {
        static Type TYPE = Type("", "IDXGIFactory4", sizeof(IDXGIFactory4));
        return TYPE;
    }

    template<>
    const Type& getType<Ghurund::Core::DirectX::DescriptorAllocator>() {
        static Type TYPE = Type("", "DescriptorAllocator", sizeof(Ghurund::Core::DirectX::DescriptorAllocator));
        return TYPE;
    }

    template<>
    const Type& getType<Ghurund::Core::DirectX::GPUResourceFactory>() {
        static Type TYPE = Type("", "GPUResourceFactory", sizeof(Ghurund::Core::DirectX::GPUResourceFactory));
        return TYPE;
    }
}