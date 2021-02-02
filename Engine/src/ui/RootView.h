#pragma once

#include "control/ControlContainer.h"
#include "application/Window.h"

namespace Ghurund::UI {
    class RootView: public ControlContainer {
    private:
        Canvas* canvas;
        uint32_t backgroundColor = 0;
        Control* prevFocusedChild = nullptr;
        Control* capturedChild = nullptr;

    public:
        RootView(UIContext& context, Canvas& canvas);

        ~RootView() {
            delete canvas;
        }

        inline uint32_t getBackgroundColor() const {
            return backgroundColor;
        }

        inline void setBackgroundColor(uint32_t color) {
            backgroundColor = color;
        }

        __declspec(property(get = getBackgroundColor, put = setBackgroundColor)) uint32_t BackgroundColor;

        virtual bool isFocused() const override {
            return context->Window.isFocused();
        }

        virtual void setCapturedChild(Control* control) override {
            this->capturedChild = control;
        }

        virtual void repaint() {
            context->Window.refresh();
        }

        virtual void invalidate();

        using Control::draw;

        inline void draw() {
            canvas->beginPaint();
            if (backgroundColor)
                canvas->clear(backgroundColor);
            draw(*canvas);
            canvas->endPaint();
        }

        virtual bool dispatchKeyEvent(const Ghurund::Input::KeyEventArgs& event) override;

        virtual bool dispatchMouseButtonEvent(const Ghurund::Input::MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const Ghurund::Input::MouseMotionEventArgs& event) override;
    };
}