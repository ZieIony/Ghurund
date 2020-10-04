#pragma once

#include "ControlParent.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "ui/ChildrenList.h"

namespace Ghurund::UI {
    class ControlGroup:public ControlParent {
    private:
        ChildrenList children;
        Control* capturedChild = nullptr;
        Control* previousReceiver = nullptr;
        Control* focusedChild = nullptr;

    protected:
        virtual void onMeasure(float parentWidth, float parentHeight) override {
            for (Control* c : Children) {
                if (!c->Visible)
                    continue;
                c->measure(
                    preferredSize.width >= 0 ? preferredSize.width : parentWidth,
                    preferredSize.height >= 0 ? preferredSize.height : parentHeight
                );
            }
        }

    public:
        ControlGroup():children(*this) {
            preferredSize.width = PreferredSize::Width::FILL;
            preferredSize.height = PreferredSize::Height::FILL;
        }

        ~ControlGroup() {
            if (capturedChild)
                capturedChild->release();
            if (previousReceiver)
                previousReceiver->release();
            if (focusedChild)
                focusedChild->release();
        }

        inline ChildrenList& getChildren() {
            return children;
        }

        inline void setChildren(const std::initializer_list<Control*>& controls) {
            children.clear();
            children.addAll(controls);
        }

        __declspec(property(get = getChildren, put = setChildren)) ChildrenList& Children;

        virtual void clearFocus() {
            if (focusedChild) {
                focusedChild->clearFocus();
                focusedChild->release();
                focusedChild = nullptr;
            }
            __super::clearFocus();
        }

        virtual void setFocus(Control* control) override {
            if (focusedChild == control)
                return;
            if (focusedChild && control)
                focusedChild->clearFocus();
            setPointer(focusedChild, control);
            __super::setFocus(this);
        }

        virtual Control* getFocus() override {
            return focusedChild;
        }

        virtual void onDraw(Canvas& canvas) override;

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override;

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event) override;

        virtual Control* find(const String& name);
    };

    typedef ScopedPointer<ControlGroup> ControlGroupPtr;
}