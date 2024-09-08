#pragma once

#include "Control.h"
#include "ui/constraint/ConstraintSet.h"

namespace Ghurund::UI {
    class ControlParent:public Control {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ControlParent::GET_TYPE();
#pragma endregion

    protected:
        Control* focusedChild = nullptr;
        Control* capturedChild = nullptr;

        ControlParent() {}

        // focusedChild and capturedChild should be null in cloned instances
        ControlParent(const ControlParent& other):Control(other) {}

        ~ControlParent() {
            if (focusedChild)
                focusedChild->release();
            if (capturedChild)
                capturedChild->release();
        }

    public:
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

        virtual const ConstraintSet& getConstraints(const Control& child) const = 0;

        virtual ConstraintSet& getConstraints(Control& child) = 0;

        virtual void setConstraints(const Control& child, const ConstraintSet& constraints) = 0;

        virtual void setConstraints(const Control& child, const ConstraintSetInitializer& constraints) = 0;

        virtual PartialConstraintSet makeDefaultConstraints() const = 0;

#ifdef _DEBUG
        virtual void validate() const override {
            _ASSERTE(!focusedChild || focusedChild->Parent == this);
        }
#endif
    };
}