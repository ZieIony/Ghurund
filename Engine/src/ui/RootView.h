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

    public:
        RootView(Ghurund::Window& window, Canvas* canvas):window(window) {
            this->canvas = canvas;
            this->window.OnFocusedChanged.add([this](Ghurund::Window& window) {
                if (Focused) {
                    if (prevFocusedChild)
                        prevFocusedChild->requestFocus();
                } else {
                    prevFocusedChild = Focus;
                    clearFocus();
                }
                return true;
            });
        }

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

        virtual void repaint() {
            window.refresh();
        }

        virtual void invalidate() {
            needsLayout = true;
            measure((float)window.Size.width, (float)window.Size.height);
            layout(0, 0, (float)window.Size.width, (float)window.Size.height);
            repaint();
        }

        using Control::draw;

        void draw() {
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

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override {
            if (!__super::dispatchMouseMotionEvent(event))
                Cursor::ARROW.set();
            return true;
        }
    };
}