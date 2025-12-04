#pragma once

#include "core/window/Window.h"
#include "engine/directx/CommandList.h"
#include "core/image/Image.h"

#include <d3d12.h>
#include <d3dx12.h>

namespace Ghurund::Engine::DirectX {
    class RenderTarget {
    private:
        ID3D12DescriptorHeap* rtvHeap = nullptr;
        ID3D12Resource* texture = nullptr;
        D3D12_CPU_DESCRIPTOR_HANDLE handle = {};
        D3D12_RESOURCE_STATES state = D3D12_RESOURCE_STATE_COMMON;
        DXGI_FORMAT format = {};
        IntSize size = {};
        WString name;

        void captureTexture(DxGraphics& graphics, ID3D12CommandQueue* commandQueue, UINT64 srcPitch, const D3D12_RESOURCE_DESC& desc, ComPtr<ID3D12Resource>& pStaging);

    public:
        ~RenderTarget() {
            uninit();
        }

        void init(DxGraphics& graphics, ID3D12Resource* texture);

        void init(DxGraphics& graphics, IntSize size, DXGI_FORMAT format);

        void uninit();

        inline void clear(CommandList& commandList, ::DirectX::XMFLOAT4 color) {
            const float clearColor[] = { color.x, color.y, color.z, color.w };
            commandList.get()->ClearRenderTargetView(handle, clearColor, 0, nullptr);
        }

        inline D3D12_CPU_DESCRIPTOR_HANDLE& getHandle() {
            return handle;
        }

        __declspec(property(get = getHandle)) D3D12_CPU_DESCRIPTOR_HANDLE& Handle;

        inline DXGI_FORMAT getFormat() const {
            return format;
        }

        __declspec(property(get = getFormat)) DXGI_FORMAT Format;

        inline const IntSize& getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) const IntSize& Size;

        ID3D12Resource* getTexture() {
            return texture;
        }

        __declspec(property(get = getTexture)) ID3D12Resource* DxTexture;

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

        inline void setName(const WString& name) {
            this->name = name;
            texture->SetName(name.Data);
        }

        inline WString getName() const {
            return name;
        }

        __declspec(property(get = getName, put = setName)) WString Name;

        void capture(DxGraphics& graphics, Ghurund::Core::Image*& image);
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::Engine::DirectX::RenderTarget>();
}