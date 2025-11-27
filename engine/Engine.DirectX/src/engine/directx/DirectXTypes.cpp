#include "ghedxpch.h"
#include "DirectXTypes.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<ID3D12CommandQueue>() {
        static Type TYPE = TypeBuilder<ID3D12CommandQueue>();
        return TYPE;
    }

    template<>
    const Type& getType<ID3D12Device>() {
        static Type TYPE = TypeBuilder<ID3D12Device>();
        return TYPE;
    }

    template<>
    const Type& getType<IDXGIFactory4>() {
        static Type TYPE = TypeBuilder<IDXGIFactory4>();
        return TYPE;
    }

    template<>
    const Type& getType<Ghurund::Engine::DirectX::DescriptorAllocator>() {
        static Type TYPE = TypeBuilder<Ghurund::Engine::DirectX::DescriptorAllocator>();
        return TYPE;
    }

    template<>
    const Type& getType<Ghurund::Engine::DirectX::GPUResourceFactory>() {
        static Type TYPE = TypeBuilder<Ghurund::Engine::DirectX::GPUResourceFactory>();
        return TYPE;
    }
}