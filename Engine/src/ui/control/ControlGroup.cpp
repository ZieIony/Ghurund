#include "ControlGroup.h"

namespace Ghurund::UI {
    void ControlGroup::draw(Canvas& canvas) {
        for (Control* c : children) {
            auto& pos = c->Position;
            canvas.translate(pos.x, pos.y);
            c->draw(canvas);
            canvas.translate(-pos.x, -pos.y);
        }
    }

    bool ControlGroup::dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
        if (capturedChild) {
            bool result = capturedChild->dispatchMouseButtonEvent(event.translate(-capturedChild->Position.x, -capturedChild->Position.y));
            if (event.Action == MouseAction::UP)
                safeRelease(capturedChild);
            if (result)
                return true;
        }
        for (size_t i = 0; i < children.Size; i++) {
            Control* c = children.get(children.Size - i - 1);
            if (c->canReceiveEvent(event) && c->dispatchMouseButtonEvent(event.translate(-c->Position.x, -c->Position.y))) {
                if (event.Action == MouseAction::DOWN)
                    setPointer(capturedChild, c);
                return true;
            }
        }
        return __super::dispatchMouseButtonEvent(event);
    }

    bool ControlGroup::dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
        if (capturedChild && capturedChild->dispatchMouseMotionEvent(event.translate(-capturedChild->Position.x, -capturedChild->Position.y)))
            return true;
        if (previousReceiver && previousReceiver != capturedChild && !previousReceiver->canReceiveEvent(event)) {
            previousReceiver->dispatchMouseMotionEvent(event.translate(-previousReceiver->Position.x, -previousReceiver->Position.y));
            previousReceiver->release();
            previousReceiver = nullptr;
        }

        safeRelease(previousReceiver);
        for (size_t i = 0; i < children.Size; i++) {
            Control* c = children.get(children.Size - i - 1);
            if (c->canReceiveEvent(event)) {
                setPointer(previousReceiver, c);
                if (c->dispatchMouseMotionEvent(event.translate(-c->Position.x, -c->Position.y)))
                    return true;
            }
        }
        return __super::dispatchMouseMotionEvent(event);
    }

    bool ControlGroup::dispatchMouseWheelEvent(const MouseWheelEventArgs& event) {
        if (capturedChild && capturedChild->dispatchMouseWheelEvent(event.translate(-capturedChild->Position.x, -capturedChild->Position.y)))
            return true;

        for (size_t i = 0; i < children.Size; i++) {
            Control* c = children.get(children.Size - i - 1);
            if (c->canReceiveEvent(event) && c->dispatchMouseWheelEvent(event.translate(-c->Position.x, -c->Position.y)))
                return true;
        }
        return __super::dispatchMouseWheelEvent(event);
    }

    Control* ControlGroup::find(const String& name) {
        if (this->name && name.operator==(this->name))
            return this;
        for (Control* c : children) {
            Control* result = c->find(name);
            if (result)
                return result;
        }
        return nullptr;
    }
}