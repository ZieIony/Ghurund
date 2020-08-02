#pragma once

#include "control/ControlContainer.h"
#include <application\Window.h>

namespace Ghurund {
    class RootView: public ControlContainer {
    public:
        unsigned int backgroundColor;

        virtual void draw(Canvas& canvas) override {
            canvas.clear(0xffe0e0e0);
            __super::draw(canvas);
        }
    };
}