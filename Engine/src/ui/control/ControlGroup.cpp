#include "ControlGroup.h"

namespace Ghurund::UI {
    bool ControlGroup::focusNext() {
        if (!Focused && Focusable && Parent) {
            Parent->setFocus(this);
            onStateChanged();
            return true;
        }
        if (Focusable)
            return false;
        size_t i = 0;
        if (focusedChild)
            i = Children.indexOf(focusedChild);
        for (i; i < Children.Size; i++) {
            Control* c = Children[i];
            if (!c->Enabled || !c->Visible)
                continue;
            if (c->focusNext())
                return true;
        }
        return false;
    }

    bool ControlGroup::focusPrevious() {
        if (!Focused && Focusable && Parent) {
            Parent->setFocus(this);
            onStateChanged();
            return true;
        }
        if (Focusable)
            return false;
        size_t i = Children.Size - 1;
        if (focusedChild)
            i = Children.indexOf(focusedChild);
        for (i; i != -1; i--) {
            Control* c = Children[i];
            if (!c->Enabled || !c->Visible)
                continue;
            if (c->focusPrevious())
                return true;
        }
        return false;
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
        if (focusedChild) {
            if (focusedChild->dispatchKeyEvent(event))
                return true;
        }
        return __super::dispatchKeyEvent(event);
    }

    bool ControlGroup::dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
        if (Focusable && event.Action == MouseAction::DOWN && !Focused)
            requestFocus();
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

        for (size_t i = 0; i < children.Size; i++) {
            Control* c = children.get(children.Size - i - 1);
            if (c->canReceiveEvent(event)) {
                if (c->dispatchMouseMotionEvent(event.translate(-c->Position.x, -c->Position.y))) {
                    setPointer(previousReceiver, c);
                    return true;
                }
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