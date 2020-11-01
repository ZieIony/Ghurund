#pragma once

#include "Control.h"

namespace Ghurund::UI {
    class ControlParent:public Control {
    protected:
        friend class Control;

        Control* focusedChild = nullptr;

    public:
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
            focusedChild = control;
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
    };
}