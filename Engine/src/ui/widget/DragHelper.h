#pragma once

#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
    class DragHelper {
    private:
        XMFLOAT2 pressControlPos = {};
        IntPoint pressMousePos = {};
        bool pressed = false;

        Event<Control> onDragged;

    public:
        DragHelper(Control& control):DragHelper(control, control) {}

        DragHelper(Control& handle, Control& content);

        inline Event<Control>& getOnDragged() {
            return onDragged;
        }

        __declspec(property(get = getOnDragged)) Event<Control>& OnDragged;
    };
}