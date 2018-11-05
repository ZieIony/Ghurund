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
        CommandList *commandList;
        D3D12_VIEWPORT viewport;
        D3D12_RECT scissorRect;
        RenderTarget *renderTarget;
        DepthBuffer *depthBuffer;

    public:
        Frame() {
            commandList = ghnew CommandList();
        }

        ~Frame() {
            delete renderTarget;
            delete depthBuffer;
            commandList->release();
        }

        Status init(Graphics &graphics, Window &window, RenderTarget *renderTarget, DepthBuffer *depthBuffer);
        Status start();
        Status finish();

        CommandList &getCommandList() {
            return *commandList;
        }
    };
}