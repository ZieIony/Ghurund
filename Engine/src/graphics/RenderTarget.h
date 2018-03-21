#pragma once

#include "application/Window.h"
#include "Frame.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>

using namespace std;

namespace Ghurund {
    class RenderTarget {
    private:
        ComPtr<ID3D12DescriptorHeap> rtvHeap;
        ComPtr<ID3D12Resource> renderTarget;
        D3D12_CPU_DESCRIPTOR_HANDLE handle;

    public:
        Status init(Graphics &graphics, ComPtr<ID3D12Resource> renderTarget) {
            D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
            rtvHeapDesc.NumDescriptors = 1;
            rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
            rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
            if(FAILED(graphics.getDevice()->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap)))) {
                Logger::log(_T("device->CreateDescriptorHeap() failed\n"));
                return Status::CALL_FAIL;
            }

            handle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
            graphics.getDevice()->CreateRenderTargetView(renderTarget.Get(), nullptr, handle);
            this->renderTarget = renderTarget;

            return Status::OK;
        }

        void clear(shared_ptr<CommandList> commandList) {
            const float clearColor[] = {0.0f, 0.2f, 0.4f, 1.0f};
            commandList->get()->ClearRenderTargetView(handle, clearColor, 0, nullptr);
        }

        D3D12_CPU_DESCRIPTOR_HANDLE &getHandle() {
            return handle;
        }

        void start(shared_ptr<CommandList> commandList) {
            commandList->get()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTarget.Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));
        }

        void finish(shared_ptr<CommandList> commandList) {
            commandList->get()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTarget.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));
        }

    };
}