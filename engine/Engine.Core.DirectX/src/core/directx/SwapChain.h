#pragma once

#include "core/collection/BufferedValue.h"
#include "core/directx/buffer/RenderTarget.h"
#include "core/directx/buffer/DepthBuffer.h"
#include "Frame.h"

#include <d3d12.h>
#include <dxgi1_4.h>

namespace Ghurund::Core {
    class SystemWindow;
}

namespace Ghurund::Core::DirectX {
    using namespace Microsoft::WRL;

    class Graphics;

    class SwapChain:public Object {
    private:
        Graphics* graphics = nullptr;
        ComPtr<IDXGISwapChain3> swapChain;
        Array<Frame>* frames = nullptr;
        uint32_t frameCount;
        size_t currentFrame = 0;
        SystemWindow* window = nullptr;
        DXGI_FORMAT format;

    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        ~SwapChain() {
            uninitBuffers();
        }

        inline bool isInitialized() const {
            return frames != nullptr;
        }

        __declspec(property(get = isInitialized)) bool Initialized;

        void init(Graphics& graphics, SystemWindow& window, uint32_t frameCount = 3);

        Status initBuffers();

        void uninitBuffers();

        Array<Frame>& getFrames() {
            return *frames;
        }

        __declspec(property(get = getFrames)) Array<Frame>& Frames;

        Frame& getCurrentFrame() {
            return frames->get(currentFrame);
        }

        __declspec(property(get = getCurrentFrame)) Frame& CurrentFrame;

        Status present();

        Status resize(const IntSize& size);

        static const Ghurund::Core::Type& GET_TYPE();
    };
}