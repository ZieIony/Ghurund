#pragma once

#include "application/Window.h"
#include "core/NamedObject.h"
#include "graphics/CommandList.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>

using namespace std;

namespace Ghurund {
    class RenderTarget: public NamedObject {
    private:
        ComPtr<ID3D12DescriptorHeap> rtvHeap;
        ComPtr<ID3D12Resource> renderTarget;
        D3D12_CPU_DESCRIPTOR_HANDLE handle;

    public:
        RenderTarget() {
#ifdef _DEBUG
            Name = _T("unnamed RenderTarget");
#endif
        }

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

#ifdef _DEBUG
            rtvHeap->SetName(L"rtvHeap");
            renderTarget->SetName(L"renderTarget");
#endif

            return Status::OK;
        }

        void clear(CommandList &commandList, XMFLOAT4 color) {
            const float clearColor[] = {color.x, color.y, color.z, color.w};
            commandList.get()->ClearRenderTargetView(handle, clearColor, 0, nullptr);
        }

        D3D12_CPU_DESCRIPTOR_HANDLE &getHandle() {
            return handle;
        }

        void start(CommandList &commandList) {
            commandList.get()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTarget.Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));
        }

        void finish(CommandList &commandList) {
            commandList.get()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(renderTarget.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));
        }

        virtual void setName(const UnicodeString &name) override {
            NamedObject::setName(name);
            renderTarget->SetName(name.getData());
        }
    };
}