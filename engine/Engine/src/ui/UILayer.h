#pragma once

#include "ui/Canvas.h"
#include "ui/RootView.h"
#include "application/Layer.h"
#include "graphics/Graphics2d.h"

namespace Ghurund::UI {
    class UILayer:public Layer {
    private:
        Graphics2D& graphics;
        Canvas* canvas;
        RootView* rootView;

    protected:
        virtual bool onFocusedChangedEvent() override {
            rootView->Focused = Focused;
            return true;
        }

    public:
        UILayer(Graphics2D& graphics, RootView* rootView):graphics(graphics) {
            canvas = ghnew Canvas();
            canvas->init(graphics.DeviceContext);
            this->rootView = rootView;
            rootView->addReference();
        }

        ~UILayer() {
            rootView->release();
            delete canvas;
        }

        virtual bool dispatchKeyEvent(const KeyEventArgs& args) {
            return rootView->dispatchKeyEvent(args);
        }

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& args) {
            return rootView->dispatchMouseButtonEvent(args);
        }

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& args) {
            return rootView->dispatchMouseMotionEvent(args);
        }

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& args) {
            return rootView->dispatchMouseWheelEvent(args);
        }

        virtual void update(const uint64_t time) override {
            rootView->onUpdate(time);
            rootView->measure((float)Size.width, (float)Size.height);
            rootView->layout(0, 0, (float)Size.width, (float)Size.height);
        }

        virtual Status draw(RenderTarget& renderTarget) override {
            graphics.beginPaint(renderTarget);
            canvas->beginPaint();
            rootView->draw(*canvas);
            canvas->endPaint();
            return graphics.endPaint();
        }
    };
}