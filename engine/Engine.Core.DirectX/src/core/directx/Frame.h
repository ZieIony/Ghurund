#pragma once

#include "core/directx/CommandList.h"
#include "core/directx/Fence.h"
#include "core/directx/Graphics.h"
#include "core/directx/buffer/DepthBuffer.h"
#include "core/directx/buffer/RenderTarget.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>

namespace Ghurund::Core::DirectX {
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
            commandList = ghnew Ghurund::Core::DirectX::CommandList();
        }

        ~Frame() {
            commandList->release();
            delete renderTarget;
            delete depthBuffer;
        }

        Status init(Graphics& graphics, D3D12_VIEWPORT& viewport, D3D12_RECT& scissorRect, RenderTarget* renderTarget, DepthBuffer* depthBuffer);

        Status start(::DirectX::XMFLOAT4* color);
        Status finish();
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