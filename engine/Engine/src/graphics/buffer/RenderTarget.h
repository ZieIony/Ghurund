#pragma once

#include "core/NamedObject.h"
#include "core/window/Window.h"
#include "graphics/CommandList.h"
#include "ui/image/Image.h"
#include "core/logging/Logger.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>

#include <dxgi1_6.h>
#include <d2d1_3.h>
#include <d3d11on12.h>

namespace Ghurund {
    class Graphics2D;

    class RenderTarget: public NamedObject<wchar_t> {
    private:
        ID3D12DescriptorHeap* rtvHeap = nullptr;
        ID3D12Resource* texture = nullptr;
        D3D12_CPU_DESCRIPTOR_HANDLE handle = {};
        D3D12_RESOURCE_STATES state = D3D12_RESOURCE_STATE_COMMON;
        DXGI_FORMAT format = {};
        ComPtr<ID3D11Resource> wrappedRenderTarget;
        ComPtr<ID2D1Bitmap1> d2dRenderTarget;
        uint32_t width = 0, height = 0;

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

        Status init(Graphics& graphics, uint32_t width, uint32_t height, DXGI_FORMAT format);

        Status init2D(Ghurund::Graphics2D& graphics2d);

        void uninit();

        inline void clear(CommandList& commandList, XMFLOAT4 color) {
            const float clearColor[] = { color.x, color.y, color.z, color.w };
            commandList.get()->ClearRenderTargetView(handle, clearColor, 0, nullptr);
        }

        inline D3D12_CPU_DESCRIPTOR_HANDLE& getHandle() {
            return handle;
        }

        __declspec(property(get = getHandle)) D3D12_CPU_DESCRIPTOR_HANDLE& Handle;

        inline ID3D11Resource* getWrappedTarget() const {
            return wrappedRenderTarget.Get();
        }

        __declspec(property(get = getWrappedTarget)) ID3D11Resource* WrappedTarget;

        inline ID2D1Bitmap1* getTarget2D() const {
            return d2dRenderTarget.Get();
        }

        __declspec(property(get = getTarget2D)) ID2D1Bitmap1* Target2D;

        inline DXGI_FORMAT getFormat() const {
            return format;
        }

        __declspec(property(get = getFormat)) DXGI_FORMAT Format;

        inline uint32_t getWidth() const {
            return width;
        }

        __declspec(property(get = getWidth)) uint32_t Width;

        inline uint32_t getHeight() const {
            return height;
        }

        __declspec(property(get = getHeight)) uint32_t Height;

        ID3D12Resource* getTexture() {
            return texture;
        }

        __declspec(property(get = getTexture)) ID3D12Resource* Texture;

        inline void start(CommandList& commandList) {
            D3D12_RESOURCE_STATES newState = D3D12_RESOURCE_STATE_RENDER_TARGET;
            if (state != newState) {
                auto transition = CD3DX12_RESOURCE_BARRIER::Transition(texture, state, newState);
                commandList.get()->ResourceBarrier(1, &transition);
                state = newState;
            }
        }

        inline void finish(CommandList& commandList, D3D12_RESOURCE_STATES newState = D3D12_RESOURCE_STATE_PRESENT) {
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

        Status capture(Graphics& graphics, Ghurund::UI::Image*& image);
    };
}

namespace Ghurund::Core {
    template<>
    String toString(const RenderTarget& renderTarget);
}
