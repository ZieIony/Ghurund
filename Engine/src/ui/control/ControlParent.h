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

        void clearChildFocus(Control* stop) {
            focusedChild = nullptr;
            if (Parent) {
                if (this != stop)
                    Parent->clearChildFocus(stop);
                onStateChanged();
            }
        }

        void setFocus(Control* control) {
            Control* focus = Focus;
            if (focus)
                focus->clearFocus();
            setPointer(focusedChild, control);
            if (Focused)
                return;
            if (Parent) {
                Parent->setFocus(this);
                onStateChanged();
            }
        }

        virtual Control* getFocus() override {
            if (Focusable)
                return this;
            if (focusedChild)
                return focusedChild->getFocus();
            return nullptr;
        }

        virtual void setCapturedChild(Control* control) {
            setPointer(capturedChild, control);
            if (Parent)
                Parent->setCapturedChild(control ? this : nullptr);
        }
    };
}