#pragma once

#include "LayerList.h"
#include "core/window/SystemWindow.h"
#include "core/input/Input.h"
#include "graphics/SwapChain.h"

namespace Ghurund {
    using namespace Ghurund::Core;

    class Application;

    class ApplicationWindow: public Ghurund::Core::SystemWindow {
#pragma region reflection
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();
        virtual const Ghurund::Core::Type& getType() const override { return TYPE; }
#pragma endregion

    private:
        SwapChain* swapChain = nullptr;
        LayerList layers;
        Application& app;

    protected:
        virtual bool onSizeChangingEvent(const IntSize& size) override {
            __super::onSizeChangingEvent(size);
            swapChain->uninitBuffers();
            return true;
        }

        virtual bool onSizeChangedEvent() override {
            layers.Size = Size;
            swapChain->resize(Size.width, Size.height);
            swapChain->initBuffers();
            __super::onSizeChangedEvent();
            return true;
        }

        virtual bool onFocusedChangedEvent() override;

    public:
        ApplicationWindow(const WindowClass& type, Application& app);

        ~ApplicationWindow() {
            uninit();
        }

        virtual Status init();

        inline void uninit() {
            delete swapChain;
            swapChain = nullptr;
        }

        inline SwapChain& getSwapChain() {
            return *swapChain;
        }

        __declspec(property(get = getSwapChain)) Ghurund::SwapChain& SwapChain;

        inline LayerList& getLayers() {
            return layers;
        }

        __declspec(property(get = getLayers)) LayerList& Layers;

        inline Application& getApplication() {
            return app;
        }

        __declspec(property(get = getApplication)) Ghurund::Application& Application;

        virtual bool onKeyEvent(const KeyEventArgs& args) override;

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& args) override;

        virtual bool onMouseMotionEvent(const MouseMotionEventArgs& args) override;

        virtual bool onMouseWheelEvent(const MouseWheelEventArgs& args) override;

        virtual void update(const uint64_t time) override;

        virtual Status paint() override;
    };
}