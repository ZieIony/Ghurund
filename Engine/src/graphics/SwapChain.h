#pragma once

#include "core/collection/BufferedValue.h"
#include "graphics/buffer/RenderTarget.h"
#include "graphics/buffer/DepthBuffer.h"
#include "core/logging/Logger.h"
#include "Frame.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>

namespace Ghurund::UI {
    class Graphics2D;
}

namespace Ghurund {
    using namespace Microsoft::WRL;

    class Graphics;
    class SystemWindow;

    class SwapChain:public Object {
    private:
        Graphics* graphics;
        Ghurund::UI::Graphics2D* graphics2d;
        ComPtr<IDXGISwapChain3> swapChain;
        Frame* frames;
        uint32_t frameCount;
        size_t currentFrame = 0;
        SystemWindow* window;
        DXGI_FORMAT format;

    protected:
        static const Ghurund::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = NoArgsConstructor<SwapChain>();
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(SwapChain))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(Object::TYPE);

            return TYPE;
        }

    public:
        ~SwapChain() {
            uninitBuffers();
        }

        Status init(Graphics& graphics, Ghurund::UI::Graphics2D* graphics2d, SystemWindow& window, uint32_t frameCount = 3);

        Status initBuffers();

        void uninitBuffers();

        Frame& getCurrentFrame() {
            return frames[currentFrame];
        }

        __declspec(property(get = getCurrentFrame)) Frame& CurrentFrame;

        Status present() {
            currentFrame++;
            currentFrame %= frameCount;

            HRESULT hr = swapChain->Present(1, 0);
            if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET) {
                return Logger::log(LogType::ERR0R, Status::DEVICE_LOST, _T("swapChain->Present() failed\n"));
            } else if (FAILED(hr)) {
                return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("swapChain->Present() failed\n"));
            }

            return Status::OK;
        }

        void resize(unsigned int width, unsigned int height);

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

    };
}