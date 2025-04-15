#pragma once

#include "core/Color.h"
#include "CommandList.h"
#include "Fence.h"
#include "Graphics.h"
#include "engine/directx/buffer/DepthBuffer.h"
#include "engine/directx/buffer/RenderTarget.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>

namespace Ghurund::Engine::DirectX {
    using namespace Microsoft::WRL;

    class Frame {
    private:
        CommandList* commandList;
        D3D12_VIEWPORT viewport = {};
        D3D12_RECT scissorRect = {};
        RenderTarget* renderTarget = nullptr;
        DepthBuffer* depthBuffer = nullptr;

    public:
        Frame() {
            commandList = ghnew Ghurund::Engine::DirectX::CommandList();
        }

        ~Frame() {
            commandList->release();
            delete renderTarget;
            delete depthBuffer;
        }

        void init(Graphics& graphics, D3D12_VIEWPORT& viewport, D3D12_RECT& scissorRect, RenderTarget* renderTarget, DepthBuffer* depthBuffer);

        void start();
        void clear(const Color* color);
        void finish();
        void flush();

        RenderTarget& getRenderTarget() {
            return *renderTarget;
        }

        __declspec(property(get = getRenderTarget)) RenderTarget& RenderTarget;

        CommandList& getCommandList() {
            return *commandList;
        }

        __declspec(property(get = getCommandList)) CommandList& CommandList;
    };
}