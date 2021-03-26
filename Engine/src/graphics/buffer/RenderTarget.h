#pragma once

#include "core/NamedObject.h"
#include "core/window/Window.h"
#include "graphics/CommandList.h"
#include "graphics/texture/Image.h"
#include "resource/ResourceContext.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>

#include <dxgi1_6.h>
#include <d2d1_3.h>
#include <d3d11on12.h>

namespace Ghurund {
    class Graphics2D;

    class RenderTarget: public NamedObject {
    private:
        ID3D12DescriptorHeap* rtvHeap = nullptr;
        ID3D12Resource* texture = nullptr;
        D3D12_CPU_DESCRIPTOR_HANDLE handle;
        D3D12_RESOURCE_STATES state = D3D12_RESOURCE_STATE_COMMON;
        DXGI_FORMAT format;
        ComPtr<ID3D11Resource> wrappedRenderTarget;
        ComPtr<ID2D1Bitmap1> d2dRenderTarget;

        Status captureTexture(Graphics& graphics, ID3D12CommandQueue* commandQueue, UINT64 srcPitch, const D3D12_RESOURCE_DESC& desc, ComPtr<ID3D12Resource>& pStaging);

    public:
        RenderTarget() {
#ifdef _DEBUG
            Name = L"unnamed RenderTarget";
#endif
        }

        ~RenderTarget() {
            uninit();
        }

        Status init(Graphics& graphics, ID3D12Resource* texture);

        Status init(Graphics& graphics, unsigned int width, unsigned int height, DXGI_FORMAT format);

        Status init2D(Ghurund::Graphics2D& graphics2d);

        void uninit();

        void clear(CommandList& commandList, XMFLOAT4 color) {
            const float clearColor[] = { color.x, color.y, color.z, color.w };
            commandList.get()->ClearRenderTargetView(handle, clearColor, 0, nullptr);
        }

        D3D12_CPU_DESCRIPTOR_HANDLE& getHandle() {
            return handle;
        }

        __declspec(property(get = getHandle)) D3D12_CPU_DESCRIPTOR_HANDLE& Handle;

        ID3D11Resource* getWrappedTarget() {
            return wrappedRenderTarget.Get();
        }

        __declspec(property(get = getWrappedTarget)) ID3D11Resource* WrappedTarget;

        ID2D1Bitmap1* getTarget2D() {
            return d2dRenderTarget.Get();
        }

        __declspec(property(get = getTarget2D)) ID2D1Bitmap1* Target2D;

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

        virtual void setName(const WString& name) override {
            NamedObject::setName(name);
            texture->SetName(name.Data);
        }

        Status capture(ResourceContext& context, Image*& image);
    };
}