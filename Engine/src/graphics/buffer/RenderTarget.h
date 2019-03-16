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
        ID3D12DescriptorHeap *rtvHeap = nullptr;
        ID3D12Resource *texture = nullptr;
        D3D12_CPU_DESCRIPTOR_HANDLE handle;
        D3D12_RESOURCE_STATES state = D3D12_RESOURCE_STATE_COMMON;
        DXGI_FORMAT format;

    public:
        RenderTarget() {
#ifdef _DEBUG
            Name = _T("unnamed RenderTarget");
#endif
        }

        ~RenderTarget() {
            uninit();
        }

        Status init(Graphics &graphics, ID3D12Resource *texture) {
            D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
            rtvHeapDesc.NumDescriptors = 1;
            rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
            rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
            if(FAILED(graphics.getDevice()->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap))))
                return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("device->CreateDescriptorHeap() failed\n"));

            handle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
            graphics.getDevice()->CreateRenderTargetView(texture, nullptr, handle);
            this->texture = texture;

#ifdef _DEBUG
            rtvHeap->SetName(L"rtvHeap");
            texture->SetName(L"renderTarget");
#endif

            return Status::OK;
        }

        Status init(Graphics &graphics, unsigned int width, unsigned int height, DXGI_FORMAT format) {
            this->format = format;

            CD3DX12_HEAP_PROPERTIES heapProperty(D3D12_HEAP_TYPE_DEFAULT);

            D3D12_RESOURCE_DESC resourceDesc;
            ZeroMemory(&resourceDesc, sizeof(resourceDesc));
            resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
            resourceDesc.Alignment = 0;
            resourceDesc.SampleDesc.Count = 1;
            resourceDesc.SampleDesc.Quality = 0;
            resourceDesc.MipLevels = 1;

            resourceDesc.DepthOrArraySize = 1;
            resourceDesc.Width = width;
            resourceDesc.Height = height;
            resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
            resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

            D3D12_CLEAR_VALUE clearVal;
            clearVal.Color[0] = 0;
            clearVal.Color[1] = 0;
            clearVal.Color[2] = 0;
            clearVal.Color[3] = 0;

            resourceDesc.Format = format;
            clearVal.Format = format;
            if(FAILED(graphics.Device->CreateCommittedResource(
                &heapProperty, D3D12_HEAP_FLAG_NONE, &resourceDesc, state, &clearVal, IID_PPV_ARGS(&texture)))) {
                return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("init RenderTarget with internal texture failed\n"));
            }

            return init(graphics, texture);
        }

        void uninit() {
            if(rtvHeap) {
                rtvHeap->Release();
                rtvHeap = nullptr;
            }
            if(texture) {
                texture->Release();
                texture = nullptr;
            }
        }

        Status resize(Graphics &graphics, unsigned int width, unsigned int height) {
            uninit();
            return init(graphics, width, height, format);
        }

        void clear(CommandList &commandList, XMFLOAT4 color) {
            const float clearColor[] = {color.x, color.y, color.z, color.w};
            commandList.get()->ClearRenderTargetView(handle, clearColor, 0, nullptr);
        }

        D3D12_CPU_DESCRIPTOR_HANDLE &getHandle() {
            return handle;
        }

        __declspec(property(get = getHandle)) D3D12_CPU_DESCRIPTOR_HANDLE &Handle;

        DXGI_FORMAT getFormat() const {
            return format;
        }

        __declspec(property(get = getFormat)) DXGI_FORMAT Format;

        void start(CommandList &commandList) {
            D3D12_RESOURCE_STATES newState = D3D12_RESOURCE_STATE_RENDER_TARGET;
            if(state!=newState) {
                commandList.get()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(texture, state, newState));
                state = newState;
            }
        }

        void finish(CommandList &commandList, D3D12_RESOURCE_STATES newState = D3D12_RESOURCE_STATE_PRESENT) {
            if(state!=newState) {
                commandList.get()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(texture, state, newState));
                state = newState;
            }
        }

        virtual void setName(const UnicodeString &name) override {
            NamedObject::setName(name);
            texture->SetName(name.getData());
        }
    };
}