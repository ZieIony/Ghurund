#pragma once

#include "LayerList.h"
#include "core/window/SystemWindow.h"
#include "core/input/Input.h"
#include "graphics/SwapChain.h"

#include "reflection_877c7fb3_5824_4c07_b617_0772d5149da1.h"

namespace Ghurund {
    class Application;

    class ApplicationWindow: public SystemWindow {
        reflection_877c7fb3_5824_4c07_b617_0772d5149da1

    private:
        SwapChain* swapChain = nullptr;
        LayerList layers;
        Application& app;

    protected:
        virtual bool onFocusedChangedEvent() override;

    public:
        ApplicationWindow(const WindowClass& type, Application& app);

        ~ApplicationWindow() {
            delete swapChain;
        }

        inline SwapChain& getSwapChain() {
            return *swapChain;
        }

        __declspec(property(get = getSwapChain)) Ghurund::SwapChain& SwapChain;

        inline LayerList& getLayers() {
            return layers;
        }

        __declspec(property(get = getLayers)) LayerList& Layers;

        virtual void setSize(uint32_t w, uint32_t h) {
            __super::setSize(w, h);
            swapChain->resize(w, h);
            layers.Size = Size;
        }

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