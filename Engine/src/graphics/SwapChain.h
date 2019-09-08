#pragma once

#include "application/Window.h"
#include "core/collection/BufferedValue.h"
#include "graphics/buffer/RenderTarget.h"
#include "graphics/buffer/DepthBuffer.h"

#include "Frame.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>

namespace Ghurund {
    using namespace Microsoft::WRL;

    class Graphics;

    class SwapChain:public Object {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(SwapChain);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<SwapChain>();

		Graphics* graphics;
        ComPtr<IDXGISwapChain3> swapChain;
        Frame* frames;
        BufferedValue<Frame> frameBuffer;
        unsigned int frameCount;
        Window* window;
        DXGI_FORMAT format;

    public:
        ~SwapChain() {
            uninitBuffers();
        }

        Status init(Graphics& graphics, Window& window, unsigned int frameCount);

        Status initBuffers();

        void uninitBuffers();

        Frame& getFrame() {
            return frameBuffer.get();
        }

        Status present() {
            frameBuffer.next();

            if (FAILED(swapChain->Present(1, 0)))
                return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("swapChain->Present() failed\n"));
            return Status::OK;
        }

        CommandList& getCommandList() {
            return frameBuffer->getCommandList();
        }

        __declspec(property(get = getCommandList)) CommandList& CommandList;

        void resize(unsigned int width, unsigned int height);

		inline static const Ghurund::Type& TYPE = TypeBuilder<SwapChain>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(Object::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

    };
}