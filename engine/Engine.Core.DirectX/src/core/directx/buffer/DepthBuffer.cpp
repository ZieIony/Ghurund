#include "ghcdxpch.h"
#include "DepthBuffer.h"

#include "core/logging/Logger.h"

namespace Ghurund::Core::DirectX {
    Status DepthBuffer::init(Graphics& graphics, unsigned int width, unsigned int height) {
        D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
        dsvHeapDesc.NumDescriptors = 1;
        dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
        dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        if (FAILED(graphics.Device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap))))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("failed to create descriptor heap\n"));

        D3D12_DEPTH_STENCIL_VIEW_DESC depthStencilDesc = {};
        depthStencilDesc.Format = DXGI_FORMAT_D32_FLOAT;
        depthStencilDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
        depthStencilDesc.Flags = D3D12_DSV_FLAG_NONE;

        D3D12_CLEAR_VALUE depthClearValue = {};
        depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;
        depthClearValue.DepthStencil.Depth = 1.0f;
        depthClearValue.DepthStencil.Stencil = 0;

        CD3DX12_HEAP_PROPERTIES heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
        CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Tex2D(DXGI_FORMAT_D32_FLOAT, width, height, 1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);
        if (FAILED(graphics.Device->CreateCommittedResource(&heapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_DEPTH_WRITE, &depthClearValue, IID_PPV_ARGS(&depthStencil))))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("failed to create depth stencil texture\n"));

        //if (FAILED(graphics.Device->CreatePlacedResource(heap, offset, resourceDesc, D3D12_RESOURCE_STATE_DEPTH_WRITE, &depthClearValue, __uuidof(*depthStencil), &depthStencil)))
        //    return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("failed to create depth stencil texture\n"));

        handle = dsvHeap->GetCPUDescriptorHandleForHeapStart();
        graphics.Device->CreateDepthStencilView(depthStencil.Get(), &depthStencilDesc, handle);

#ifdef _DEBUG
        dsvHeap->SetName(L"dsvHeap");
        depthStencil->SetName(L"depthStencil");
#endif

        return Status::OK;
    }
}