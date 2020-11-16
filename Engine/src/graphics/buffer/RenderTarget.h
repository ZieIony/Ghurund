#pragma once

#include "application/Window.h"
#include "core/NamedObject.h"
#include "graphics/CommandList.h"
#include "graphics/texture/Image.h"
#include "resource/ResourceContext.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>

namespace Ghurund {
    class RenderTarget: public NamedObject<String> {
    private:
        ID3D12DescriptorHeap* rtvHeap = nullptr;
        ID3D12Resource* texture = nullptr;
        D3D12_CPU_DESCRIPTOR_HANDLE handle;
        D3D12_RESOURCE_STATES state = D3D12_RESOURCE_STATE_COMMON;
        DXGI_FORMAT format;

        Status captureTexture(Graphics& graphics, ID3D12CommandQueue* commandQueue, UINT64 srcPitch, const D3D12_RESOURCE_DESC& desc, ComPtr<ID3D12Resource>& pStaging);

    public:
        RenderTarget() {
#ifdef _DEBUG
            Name = _T("unnamed RenderTarget");
#endif
        }

        ~RenderTarget() {
            uninit();
        }

        Status init(Graphics& graphics, ID3D12Resource* texture);

        Status init(Graphics& graphics, unsigned int width, unsigned int height, DXGI_FORMAT format);

        void uninit();

        Status resize(Graphics& graphics, unsigned int width, unsigned int height) {
            uninit();
            return init(graphics, width, height, format);
        }

        void clear(CommandList& commandList, XMFLOAT4 color) {
            const float clearColor[] = {color.x, color.y, color.z, color.w};
            commandList.get()->ClearRenderTargetView(handle, clearColor, 0, nullptr);
        }

        D3D12_CPU_DESCRIPTOR_HANDLE& getHandle() {
            return handle;
        }

        __declspec(property(get = getHandle)) D3D12_CPU_DESCRIPTOR_HANDLE& Handle;

        DXGI_FORMAT getFormat() const {
            return format;
        }

        __declspec(property(get = getFormat)) DXGI_FORMAT Format;

        ID3D12Resource* getTexture() {
            return texture;
        }

        __declspec(property(get = getTexture)) ID3D12Resource* Texture;

        void start(CommandList& commandList) {
            D3D12_RESOURCE_STATES newState = D3D12_RESOURCE_STATE_RENDER_TARGET;
            if (state != newState) {
                auto transition = CD3DX12_RESOURCE_BARRIER::Transition(texture, state, newState);
                commandList.get()->ResourceBarrier(1, &transition);
                state = newState;
            }
        }

        void finish(CommandList& commandList, D3D12_RESOURCE_STATES newState = D3D12_RESOURCE_STATE_PRESENT) {
            if (state != newState) {
                auto transition = CD3DX12_RESOURCE_BARRIER::Transition(texture, state, newState);
                commandList.get()->ResourceBarrier(1, &transition);
                state = newState;
            }
        }

        virtual void setName(const String& name) override {
            NamedObject<String>::setName(name);
            texture->SetName((UnicodeString)name);
        }

        Status capture(ResourceContext& context, Image*& image);
    };
}