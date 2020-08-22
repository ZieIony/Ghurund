#pragma once

#include "Control.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "ui/ChildrenList.h"

namespace Ghurund::UI {
    class ControlGroup :public Control {
    private:
        ChildrenList children;
        Control* capturedChild = nullptr;
        Control* previousReceiver = nullptr;

    protected:
        inline void measureMaxWidth() {
            if (preferredSize.width == PreferredSize::Width::WRAP) {
                measuredSize.x = 0;
                for (Control* c : Children)
                    measuredSize.x = std::max(measuredSize.x, (float)c->MeasuredSize.x);
            } else if (preferredSize.width != PreferredSize::Width::FILL) {
                measuredSize.x = (float)preferredSize.width;
            }
        }

        inline void measureMaxHeight() {
            if (preferredSize.height == PreferredSize::Height::WRAP) {
                measuredSize.y = 0;
                for (Control* c : Children)
                    measuredSize.y = std::max(measuredSize.y, (float)c->MeasuredSize.y);
            } else if (preferredSize.height != PreferredSize::Height::FILL) {
                measuredSize.y = (float)preferredSize.height;
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
        }

        inline ChildrenList& getChildren() {
            return children;
        }

        __declspec(property(get = getChildren)) ChildrenList& Children;

        virtual void onMeasure() override {
            for (Control* c : Children)
                c->measure();
        }

        virtual void draw(Canvas& canvas) override;

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override;

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event) override;

        virtual Control* find(const String& name);
    };
}