#pragma once

#include "control/HoverableView.h"
#include <application\Window.h>

namespace Ghurund::UI {
    class RootView: public ControlContainer {
    private:
        Ghurund::Window& window;
        Canvas* canvas;
        uint32_t backgroundColor = 0;
        Control* prevFocusedChild = nullptr;
        Control* capturedChild = nullptr;

    public:
        RootView(Ghurund::Window& window, Canvas* canvas);

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
            return window.isFocused();
        }

        virtual void setCapturedChild(Control* control) override {
            this->capturedChild = control;
        }

        virtual void repaint() {
            window.refresh();
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

        virtual Ghurund::Window* getWindow() const {
            return &window;
        }

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override;

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;
    };
}