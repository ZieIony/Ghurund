#pragma once

#include "Control.h"

namespace Ghurund::UI {
    class ControlParent:public Control {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();
#pragma endregion

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

        virtual Control* getFocus() const override {
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
        virtual void validate() const override {
            _ASSERTE(!focusedChild || focusedChild->Parent == this);
        }
#endif
    };
}