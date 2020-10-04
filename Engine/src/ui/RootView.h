#pragma once

#include "control/HoverableView.h"
#include <application\Window.h>

namespace Ghurund::UI {
    class RootView: public HoverableView {
    private:
        Ghurund::Window& window;

    public:
        RootView(Ghurund::Window& window):window(window) {}

        virtual void repaint() {
            window.refresh();
        }

        virtual void invalidate() {
            needsLayout = true;
            measure(window.Size.x, window.Size.y);
            layout(0, 0, window.Size.x, window.Size.y);
            repaint();
        }

        virtual Ghurund::Window* getWindow() const {
            return &window;
        }

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override {
            if (!__super::dispatchMouseMotionEvent(event))
                Cursor::ARROW.set();
            return true;
        }
    };
}