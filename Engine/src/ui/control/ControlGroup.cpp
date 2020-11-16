#include "ControlGroup.h"

namespace Ghurund::UI {
    bool ControlGroup::focusNext() {
        if (__super::focusNext())
            return true;
        if (Focusable)
            return false;
        size_t i = 0;
        if (focusedChild)
            i = Children.indexOf(focusedChild);
        for (i; i < Children.Size; i++) {
            if (Children[i]->focusNext())
                return true;
        }
        return false;
    }

    bool ControlGroup::focusPrevious() {
        if (__super::focusPrevious())
            return true;
        if (Focusable)
            return false;
        size_t i = Children.Size - 1;
        if (focusedChild)
            i = Children.indexOf(focusedChild);
        for (i; i != -1; i--) {
            if (Children[i]->focusPrevious())
                return true;
        }
        return false;
    }

    bool ControlGroup::focusUp() {
        if (__super::focusUp())
            return true;
        if (Focusable)
            return false;
        return focusedChild && focusedChild->focusUp();
    }

    bool ControlGroup::focusDown() {
        if (__super::focusDown())
            return true;
        if (Focusable)
            return false;
        return focusedChild && focusedChild->focusDown();
    }

    bool ControlGroup::focusLeft() {
        if (__super::focusLeft())
            return true;
        if (Focusable)
            return false;
        return focusedChild && focusedChild->focusLeft();
    }

    bool ControlGroup::focusRight() {
        if (__super::focusRight())
            return true;
        if (Focusable)
            return false;
        return focusedChild && focusedChild->focusRight();
    }

    void ControlGroup::onDraw(Canvas& canvas) {
        canvas.save();
        canvas.clipRect(0, 0, Size.width, Size.height);
        for (Control* c : children) {
            if (!c->Visible)
                continue;
            c->draw(canvas);
        }
        canvas.restore();
    }

    bool ControlGroup::dispatchKeyEvent(const KeyEventArgs& event) {
        if (focusedChild && focusedChild->dispatchKeyEvent(event))
            return true;
        for (size_t i = 0; i < children.Size; i++) {
            Control* c = children.get(children.Size - i - 1);
            if (c->dispatchKeyEvent(event))
                return true;
        }
        return __super::dispatchKeyEvent(event);
    }

    bool ControlGroup::dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
        if (capturedChild) {
            auto e = event.translate(-capturedChild->Position.x, -capturedChild->Position.y, capturedChild->canReceiveEvent(event));
            return capturedChild->dispatchMouseButtonEvent(e);
        }

        for (size_t i = 0; i < children.Size; i++) {
            Control* c = children.get(children.Size - i - 1);
            if (c->canReceiveEvent(event) && c->dispatchMouseButtonEvent(event.translate(-c->Position.x, -c->Position.y, true)))
                return true;
        }
        return __super::dispatchMouseButtonEvent(event);
    }

    bool ControlGroup::dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
        if (capturedChild) {
            auto e = event.translate(-capturedChild->Position.x, -capturedChild->Position.y, capturedChild->canReceiveEvent(event));
            return capturedChild->dispatchMouseMotionEvent(e);
        }
        if (previousReceiver && !previousReceiver->canReceiveEvent(event)) {
            previousReceiver->dispatchMouseMotionEvent(event.translate(-previousReceiver->Position.x, -previousReceiver->Position.y, false));
            previousReceiver->release();
            previousReceiver = nullptr;
        }

        for (size_t i = 0; i < children.Size; i++) {
            Control* c = children.get(children.Size - i - 1);
            if (c->canReceiveEvent(event)) {
                setPointer(previousReceiver, c);
                return c->dispatchMouseMotionEvent(event.translate(-c->Position.x, -c->Position.y, true));
            }
        }
        return __super::dispatchMouseMotionEvent(event);
    }

    bool ControlGroup::dispatchMouseWheelEvent(const MouseWheelEventArgs& event) {
        for (size_t i = 0; i < children.Size; i++) {
            Control* c = children.get(children.Size - i - 1);
            if (c->canReceiveEvent(event) && c->dispatchMouseWheelEvent(event.translate(-c->Position.x, -c->Position.y)))
                return true;
        }
        return __super::dispatchMouseWheelEvent(event);
    }

    Control* ControlGroup::find(const String& name) {
        if (this->Name && this->Name->operator==(name))
            return this;
        for (Control* c : children) {
            Control* result = c->find(name);
            if (result)
                return result;
        }
        return nullptr;
    }
}