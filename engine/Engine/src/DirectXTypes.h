#pragma once

#include "core/reflection/Type.h"
#include "graphics/buffer/DescriptorHeap.h"
#include "graphics/memory/GPUResourceFactory.h"

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
    const Type& getType<DescriptorAllocator>();

    template<>
    const Type& getType<GPUResourceFactory>();
}
