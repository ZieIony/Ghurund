#include "ghcdxpch.h"
#include "GPUResourceFactory.h"

#include "core/math/MathUtils.h"
#include "core/directx/Graphics.h"
#include "core/logging/Logger.h"

namespace Ghurund::Core::DirectX {
    GPUResourceFactory::GPUResourceFactory(Graphics& graphics):graphics(graphics) {
        depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;
        depthClearValue.DepthStencil.Depth = 1.0f;
        depthClearValue.DepthStencil.Stencil = 0;

		HeapAllocator* uploadAllocator = ghnew HeapAllocator(graphics, 100_MB, nullptr,
			D3D12_HEAP_TYPE_UPLOAD, D3D12_HEAP_FLAG_DENY_NON_RT_DS_TEXTURES | D3D12_HEAP_FLAG_DENY_RT_DS_TEXTURES);
        allocators.set(D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD, uploadAllocator);
		HeapAllocator* defaultAllocator = ghnew HeapAllocator(graphics, 100_MB, nullptr,
			D3D12_HEAP_TYPE_DEFAULT, D3D12_HEAP_FLAG_DENY_BUFFERS | D3D12_HEAP_FLAG_DENY_RT_DS_TEXTURES);
        allocators.set(D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_DEFAULT, defaultAllocator);
    }

    GPUResourcePointer* GPUResourceFactory::create(D3D12_HEAP_TYPE heapType, CD3DX12_RESOURCE_DESC resourceDesc, D3D12_RESOURCE_STATES initialState, ID3D12Resource** resource) {
        HeapAllocator* heap = allocators.get(heapType);
        void* address = (void*)heap->allocate(resourceDesc.Width);
        if ((uint64_t)address == heap->Size) {
            Logger::log(LogType::ERR0R, _T("failed to allocate memory for resource\n"));
            return nullptr;
        }
        if (FAILED(graphics.Device->CreatePlacedResource(heap->Heap, (uint64_t)address, &resourceDesc, initialState, resourceDesc.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER ? nullptr : &depthClearValue, IID_PPV_ARGS(resource)))) {
            Logger::log(LogType::ERR0R, _T("failed to create placed resource\n"));
            return nullptr;
        }

        return ghnew GPUResourcePointer(heap, address, *resource);
    }
}
