#pragma once

#include "application/Window.h"
#include "Fence.h"
#include "Graphics.h"
#include "CommandList.h"
#include "RenderTarget.h"
#include "DepthBuffer.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>

using namespace Microsoft::WRL;

namespace Ghurund {
    class Frame {
    private:
        shared_ptr<CommandList> commandList;
        D3D12_VIEWPORT viewport;
        D3D12_RECT scissorRect;
        shared_ptr<RenderTarget> renderTarget;
        shared_ptr<DepthBuffer> depthBuffer;

    public:
        Status init(Graphics &graphics, Window &window, shared_ptr<RenderTarget> renderTarget, shared_ptr<DepthBuffer> depthBuffer);
        Status start();
        Status finish();

        shared_ptr<CommandList> getCommandList() {
            return commandList;
        }
    };
}