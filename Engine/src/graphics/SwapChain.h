#pragma once

#include "application/Window.h"
#include "collection/BufferedValue.h"
#include "graphics/buffer/RenderTarget.h"
#include "graphics/buffer/DepthBuffer.h"

#include "Frame.h"

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
        unsigned int frameCount;
        Window *window;
        DXGI_FORMAT format;

    public:
        ~SwapChain() {
            uninitBuffers();
        }

        Status init(Graphics &graphics, Window &window, unsigned int frameCount);

        Status initBuffers(Graphics &graphics);

        void uninitBuffers();

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

        CommandList &getCommandList() {
            return frameBuffer->getCommandList();
        }

        __declspec(property(get = getCommandList)) CommandList &CommandList;

        void resize(Graphics &graphics, unsigned int width, unsigned int height);
    };
}