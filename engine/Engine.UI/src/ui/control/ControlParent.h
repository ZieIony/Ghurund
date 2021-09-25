#pragma once

#include "Control.h"

namespace Ghurund::UI {
    class ControlParent:public Control {
#pragma region reflection
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();
        virtual const Ghurund::Core::Type& getType() const override { return TYPE; }
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