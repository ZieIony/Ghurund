#pragma once

#include "Control.h"

namespace Ghurund::UI {
    class ControlParent:public Control {
    protected:
        friend class Control;

        Control* focusedChild = nullptr;
        Control* capturedChild = nullptr;

    public:
        ~ControlParent() {
            if (focusedChild)
                focusedChild->release();
            if (capturedChild)
                capturedChild->release();
        }

        void setFocus(Control* control) {
            setPointer(focusedChild, control);
        }

        virtual Control* getFocus() override {
            return focusedChild;
        }

        virtual void setCapturedChild(Control* control) {
            setPointer(capturedChild, control);
            if (Parent)
                Parent->setCapturedChild(control ? this : nullptr);
        }
    };
}