#pragma once

#include "Control.h"

namespace Ghurund::UI {
    class ControlContainer : public Control {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(ControlContainer);

        Control* child = nullptr;

    public:
        ~ControlContainer() {
            if (child) {
                child->Parent = nullptr;
                child->release();
            }
        }

        inline Control* getChild() {
            return child;
        }

        inline void setChild(Control* child) {
            if (this->child)
                this->child->Parent = nullptr;
            setPointer(this->child, child);
            if (this->child)
                this->child->Parent = this;
        }

        __declspec(property(get = getChild, put = setChild)) Control* Child;

        virtual void measure() override;

        void layout(float x, float y, float width, float height) {
            __super::layout(x, y, width, height);
            if (child)
                child->layout(0, 0, width, height);
        }

        void draw(Canvas& canvas) {
            if (child) {
                auto& pos = child->Position;
                canvas.translate(pos.x, pos.y);
                child->draw(canvas);
                canvas.translate(-pos.x, -pos.y);
            }
        }
        /*
        virtual bool dispatchKeyEvent(const KeyEventArgs& event) {
            if (child->Visible && child->Enabled &&
                event.Position.x >= child->Position.x && event.Position.x <= child->Position.x + child->Size.x &&
                event.Position.y >= child->Position.y && event.Position.y <= child->Position.y + child->Size.y) {
                XMINT2 childEventPos = { (int32_t)(event.Position.x - child->Position.x), (int32_t)(event.Position.y - child->Position.y) };
                KeyEventArgs childEvent = KeyEventArgs(childEventPos, event.Action, event.Button, event.Time);
                if (child->dispatchKeyEvent(childEvent))
                    return true;
            }
            return __super::dispatchKeyEvent(event);
        }*/

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event);

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
            if (child->Visible && child->Enabled &&
                event.Position.x >= child->Position.x && event.Position.x <= child->Position.x + child->Size.x &&
                event.Position.y >= child->Position.y && event.Position.y <= child->Position.y + child->Size.y) {
                XMINT2 childEventPos = { (int32_t)(event.Position.x - child->Position.x), (int32_t)(event.Position.y - child->Position.y) };
                MouseMotionEventArgs childEvent = MouseMotionEventArgs(childEventPos, event.Delta, event.Time);
                if (child->dispatchMouseMotionEvent(childEvent))
                    return true;
            }
            return __super::dispatchMouseMotionEvent(event);
        }

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event) {
            if (child->Visible && child->Enabled &&
                event.Position.x >= child->Position.x && event.Position.x <= child->Position.x + child->Size.x &&
                event.Position.y >= child->Position.y && event.Position.y <= child->Position.y + child->Size.y) {
                XMINT2 childEventPos = { (int32_t)(event.Position.x - child->Position.x), (int32_t)(event.Position.y - child->Position.y) };
                MouseWheelEventArgs childEvent = MouseWheelEventArgs(childEventPos, event.Wheel, event.Delta, event.Time);
                if (child->dispatchMouseWheelEvent(childEvent))
                    return true;
            }
            return __super::dispatchMouseWheelEvent(event);
        }

        virtual Control* find(const String& name) {
            if (this->name && name.operator==(this->name))
                return this;
            if (child)
                return child->find(name);
            return nullptr;
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<ControlContainer>(NAMESPACE_NAME, CLASS_NAME)
            .withSupertype(Control::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}