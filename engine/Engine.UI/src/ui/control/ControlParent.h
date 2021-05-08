#pragma once

#include "Control.h"

#include "reflection_718b3d8f_c238_4e88_a9a3_263adce33482.h"

namespace Ghurund::UI {
    class ControlParent:public Control {
        reflection_718b3d8f_c238_4e88_a9a3_263adce33482

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

        __declspec(property(get = getFocus, put = setFocus)) Control* Focus;

        inline void setCapturedChild(Control* control) {
            setPointer(capturedChild, control);
            if (Parent)
                Parent->CapturedChild = (control ? this : nullptr);
        }

        __declspec(property(put = setCapturedChild)) Control* CapturedChild;

#ifdef _DEBUG
        virtual void validate() override {
            _ASSERTE(!focusedChild || focusedChild->Parent == this);
        }
#endif
    };
}