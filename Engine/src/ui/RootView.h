#pragma once

#include "control/ControlContainer.h"
#include <application\Window.h>

namespace Ghurund::UI {
    class RootView: public ControlContainer {
    public:
        unsigned int backgroundColor;

        Window& window;

        RootView(Window& window):window(window) {}

        virtual void draw(Canvas& canvas) override {
            canvas.clear(0xffe0e0e0);
            __super::draw(canvas);
        }

        virtual void repaint() {
            window.refresh();
        }

        virtual void invalidate() {
            measure();
            layout(0, 0, Size.x, Size.y);
        }

    };
}