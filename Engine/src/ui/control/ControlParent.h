#pragma once

#include "Control.h"

namespace Ghurund::UI {
    class ControlParent:public Control {
    public:
        virtual void setFocus(Control* control) {
            if (focused)
                return;
            focused = true;
            onStateChanged();
            if (parent)
                parent->setFocus(this);
        }

        virtual Control* getFocus() = 0;

        __declspec(property(get = getFocus, put = setFocus)) Control* Focus;
    };
}