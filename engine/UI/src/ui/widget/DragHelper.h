#pragma once

#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class DragHelper {
    private:
        FloatPoint pressControlPos = {};
        IntPoint pressMousePos = {};
        bool pressed = false;

    public:
        DragHelper(Control& control):DragHelper(control, control) {}

        DragHelper(Control& handle, Control& content);

        Event<Control> dragged;
    };
}