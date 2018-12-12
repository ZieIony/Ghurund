#pragma once

#include "application/Window.h"
#include "graphics/CommandList.h"
#include "graphics/Fence.h"
#include "graphics/Graphics.h"
#include "graphics/buffer/DepthBuffer.h"
#include "graphics/buffer/RenderTarget.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>

using namespace Microsoft::WRL;

namespace Ghurund {
    class Frame {
    private:
        CommandList *commandList;
        D3D12_VIEWPORT viewport;
        D3D12_RECT scissorRect;
        RenderTarget *renderTarget;
        DepthBuffer *depthBuffer;

    public:
        Frame() {
            commandList = ghnew Ghurund::CommandList();
        }

        ~Frame() {
            commandList->release();
            delete renderTarget;
            delete depthBuffer;
        }

        Status init(Graphics &graphics, Window &window, RenderTarget *renderTarget, DepthBuffer *depthBuffer);
        Status start();
        Status finish();

        CommandList &getCommandList() {
            return *commandList;
        }

        __declspec(property(get = getCommandList)) CommandList &CommandList;
    };
}