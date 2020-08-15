#pragma once

#include "Control.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "ui/ChildrenList.h"

namespace Ghurund::UI {
    class ControlGroup:public Control {
    private:
        ChildrenList children;
        Control* capturedChild = nullptr;

    protected:
        void measureMaxWidth() {
            if (preferredSize.width == PreferredSize::Width::WRAP) {
                measuredSize.x = 0;
                for (Control* c : Children)
                    measuredSize.x = std::max(measuredSize.x, (float)c->MeasuredSize.x);
            } else if (preferredSize.width != PreferredSize::Width::FILL) {
                measuredSize.x = (float)preferredSize.width;
            }
        }

        void measureMaxHeight() {
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

        ChildrenList& getChildren() {
            return children;
        }

        __declspec(property(get = getChildren)) ChildrenList& Children;

        virtual void measure() override {
            for (Control* c : Children)
                c->measure();
        }

        virtual void layout(float x, float y, float width, float height) = 0 {
            __super::layout(x, y, width, height);
        }

        virtual void draw(Canvas &canvas) override {

            for (Control* c : children) {
                auto &pos = c->Position;
                canvas.translate(pos.x, pos.y);
                c->draw(canvas);
                canvas.translate(-pos.x, -pos.y);
            }
        }

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
            if (capturedChild) {
                XMINT2 childEventPos = { (int32_t)(event.Position.x - capturedChild->Position.x), (int32_t)(event.Position.y - capturedChild->Position.y) };
                MouseButtonEventArgs childEvent = MouseButtonEventArgs(childEventPos, event.Action, event.Button, event.Time);
                bool result = capturedChild->dispatchMouseButtonEvent(childEvent);
                if (event.Action == MouseAction::UP)
                    capturedChild = nullptr;
                if(result)
                    return true;
            }
            for (Control* c : Children) {
                if (c->Visible && c->Enabled &&
                    event.Position.x >= c->Position.x && event.Position.x <= c->Position.x + c->Size.x &&
                    event.Position.y >= c->Position.y && event.Position.y <= c->Position.y + c->Size.y) {
                    XMINT2 childEventPos = { (int32_t)(event.Position.x - c->Position.x), (int32_t)(event.Position.y - c->Position.y) };
                    MouseButtonEventArgs childEvent = MouseButtonEventArgs(childEventPos, event.Action, event.Button, event.Time);
                    if (c->dispatchMouseButtonEvent(childEvent)) {
                        if (event.Action == MouseAction::DOWN)
                            capturedChild = c;
                        return true;
                    }
                }
            }
            return __super::dispatchMouseButtonEvent(event);
        }

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
            return __super::dispatchMouseMotionEvent(event);
        }

        virtual Control* find(const String& name) {
            if (this->name && name.operator==(this->name))
                return this;
            for (Control* c : children) {
                Control* result = c->find(name);
                if(result)
                    return result;
            }
            return nullptr;
        }
    };
}