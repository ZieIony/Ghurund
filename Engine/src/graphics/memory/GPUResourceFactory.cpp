#include "GPUResourceFactory.h"
#include "graphics/Graphics.h"

namespace Ghurund {
    GPUResourceFactory::GPUResourceFactory(Graphics & graphics):graphics(graphics) {
        depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;
        depthClearValue.DepthStencil.Depth = 1.0f;
        depthClearValue.DepthStencil.Stencil = 0;

        allocators.set(D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD, ghnew HeapAllocator(graphics, 100*1024*1024, nullptr, D3D12_HEAP_TYPE_UPLOAD, D3D12_HEAP_FLAG_DENY_NON_RT_DS_TEXTURES|D3D12_HEAP_FLAG_DENY_RT_DS_TEXTURES));
        allocators.set(D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_DEFAULT, ghnew HeapAllocator(graphics, 100*1024*1024, nullptr, D3D12_HEAP_TYPE_DEFAULT, D3D12_HEAP_FLAG_DENY_BUFFERS|D3D12_HEAP_FLAG_DENY_RT_DS_TEXTURES));
    }

    GPUResourcePointer *GPUResourceFactory::create(D3D12_HEAP_TYPE heapType, CD3DX12_RESOURCE_DESC resourceDesc, D3D12_RESOURCE_STATES initialState, ID3D12Resource ** resource) {
        HeapAllocator *heap = allocators.get(heapType);
        memory_t address = heap->allocate(resourceDesc.Width);
        if(FAILED(graphics.Device->CreatePlacedResource(heap->Heap, address, &resourceDesc, initialState, resourceDesc.Dimension==D3D12_RESOURCE_DIMENSION_BUFFER?nullptr:&depthClearValue, IID_PPV_ARGS(resource)))) {
            Logger::log(LogType::ERR0R, _T("failed to create placed resource\n"));
            return nullptr;
        }

        return ghnew GPUResourcePointer(heap, address, *resource);
    }
}
