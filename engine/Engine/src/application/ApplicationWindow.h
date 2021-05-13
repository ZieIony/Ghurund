#pragma once

#include "LayerList.h"
#include "core/window/SystemWindow.h"
#include "core/input/Input.h"
#include "graphics/SwapChain.h"

namespace Ghurund {
    class Application;

    class ApplicationWindow: public SystemWindow {
    private:
        SwapChain* swapChain = nullptr;
        LayerList layers;
        Application& app;

    protected:
        static const Ghurund::Type& GET_TYPE();

        virtual bool onFocusedChangedEvent() override;

    public:
        ApplicationWindow(const WindowClass& type, Application& app);

        ~ApplicationWindow() {
            delete swapChain;
        }

        inline SwapChain* getSwapChain() {
            return swapChain;
        }

        inline void setSwapChain(std::unique_ptr<SwapChain> swapChain) {
            this->swapChain = swapChain.release();
        }

        __declspec(property(get = getSwapChain, put = setSwapChain)) SwapChain* SwapChain;

        inline LayerList& getLayers() {
            return layers;
        }

        __declspec(property(get = getLayers)) LayerList& Layers;

        virtual void setSize(uint32_t w, uint32_t h) {
            __super::setSize(w, h);
            if (swapChain)
                swapChain->resize(w, h);
            layers.Size = Size;
        }

        inline Application& getApplication() {
            return app;
        }

        __declspec(property(get = getApplication)) Application& Application;

        virtual bool onKeyEvent(const KeyEventArgs& args) override;

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& args) override;

        virtual bool onMouseMotionEvent(const MouseMotionEventArgs& args) override;

        virtual bool onMouseWheelEvent(const MouseWheelEventArgs& args) override;

        virtual void update(const uint64_t time) override;

        virtual Status paint() override {
            return layers.draw(swapChain->CurrentFrame.RenderTarget);
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}