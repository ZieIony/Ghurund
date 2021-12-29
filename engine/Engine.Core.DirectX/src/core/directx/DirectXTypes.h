#pragma once

#include "core/reflection/Type.h"
#include "core/directx/buffer/DescriptorHeap.h"
#include "core/directx/memory/GPUResourceFactory.h"

#include <d3d12.h>
#include <dxgi1_4.h>

namespace Ghurund::Core {
    template<>
    const Type& getType<ID3D12CommandQueue>();

    template<>
    const Type& getType<ID3D12Device>();

    template<>
    const Type& getType<IDXGIFactory4>();

    template<>
    const Type& getType<Ghurund::Core::DirectX::DescriptorAllocator>();

    template<>
    const Type& getType<Ghurund::Core::DirectX::GPUResourceFactory>();
}
