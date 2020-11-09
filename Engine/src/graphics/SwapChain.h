#pragma once

#include "application/SystemWindow.h"
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
		Graphics* graphics;
        ComPtr<IDXGISwapChain3> swapChain;
        Frame* frames;
        BufferedValue<Frame> frameBuffer;
        unsigned int frameCount;
        SystemWindow* window;
        DXGI_FORMAT format;

        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(SwapChain))
                .withConstructor(NoArgsConstructor<SwapChain>())
                .withSupertype(Object::TYPE);

            return TYPE;
        }

    public:
        ~SwapChain() {
            uninitBuffers();
        }

        Status init(Graphics& graphics, SystemWindow& window, unsigned int frameCount);

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

		inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

    };
}