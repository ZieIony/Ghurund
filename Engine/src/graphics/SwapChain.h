#pragma once

#include "application/Window.h"
#include "Frame.h"
#include "RenderTarget.h"
#include "DepthBuffer.h"
#include "collection/BufferedValue.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>

using namespace Microsoft::WRL;

namespace Ghurund {
    class Graphics;

    class SwapChain {
    private:
        ComPtr<IDXGISwapChain3> swapChain;
        Frame *frames;
        BufferedValue<Frame> frameBuffer;

    public:
        ~SwapChain() {
            delete[] frames;
            frames = nullptr;
        }

        Status init(Graphics &graphics, Window &window, unsigned int frameCount);

        Status startFrame() {
            return frameBuffer->start();
        }

        Status finishFrame() {
            frameBuffer->finish();
            frameBuffer.next();

            if(FAILED(swapChain->Present(1, 0))) {
                Logger::log(_T("swapChain->Present() failed\n"));
                return Status::CALL_FAIL;
            }
            return Status::OK;
        }

        shared_ptr<CommandList> getCommandList() {
            return frameBuffer->getCommandList();
        }
    };
}