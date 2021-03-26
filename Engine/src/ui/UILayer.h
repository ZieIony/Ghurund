#pragma once

#include "ui/Canvas.h"
#include "ui/RootView.h"
#include "core/window/Layer.h"
#include "graphics/Graphics2d.h"

namespace Ghurund::UI {
    class UILayer:public Layer {
    private:
        Graphics2D& graphics;
        SwapChain& swapChain;
        Canvas* canvas;
        RootView* rootView;

    protected:
        virtual bool onFocusedChangedEvent() override {
            rootView->Focused = Focused;
            return true;
        }

    public:
        UILayer(Graphics2D& graphics, SwapChain& swapChain, RootView* rootView):graphics(graphics), swapChain(swapChain) {
            canvas = ghnew Canvas();
            canvas->init(graphics.DeviceContext);
            this->rootView = rootView;
            rootView->addReference();
        }

        ~UILayer() {
            rootView->release();
            delete canvas;
        }

        virtual bool dispatchKeyEvent(const Ghurund::KeyEventArgs& args) {
            return rootView->dispatchKeyEvent(args);
        }

        virtual bool dispatchMouseButtonEvent(const Ghurund::MouseButtonEventArgs& args) {
            return rootView->dispatchMouseButtonEvent(args);
        }

        virtual bool dispatchMouseMotionEvent(const Ghurund::MouseMotionEventArgs& args) {
            return rootView->dispatchMouseMotionEvent(args);
        }

        virtual bool dispatchMouseWheelEvent(const Ghurund::MouseWheelEventArgs& args) {
            return rootView->dispatchMouseWheelEvent(args);
        }

        virtual void update(const uint64_t time) override {
            rootView->onUpdate(time);
            rootView->measure((float)Size.width, (float)Size.height);
            rootView->layout(0, 0, (float)Size.width, (float)Size.height);
        }

        virtual Status draw() override {
            graphics.beginPaint(swapChain.CurrentFrame.RenderTarget);
            canvas->beginPaint();
            rootView->draw(*canvas);
            canvas->endPaint();
            return graphics.endPaint();
        }
    };
}