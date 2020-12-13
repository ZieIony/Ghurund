#include "ControlContainer.h"

namespace Ghurund::UI {
    bool ControlContainer::focusNext() {
        if (__super::focusNext())
            return true;
        if (Focusable)
            return false;
        return child && child->focusNext();
    }

    bool ControlContainer::focusPrevious() {
        if (__super::focusPrevious())
            return true;
        if (Focusable)
            return false;
        return child && child->focusPrevious();
    }

    bool ControlContainer::focusUp() {
        if (__super::focusUp())
            return true;
        if (Focusable)
            return false;
        return child && child->focusUp();
    }

    bool ControlContainer::focusDown() {
        if (__super::focusDown())
            return true;
        if (Focusable)
            return false;
        return child && child->focusDown();
    }

    bool ControlContainer::focusLeft() {
        if (__super::focusLeft())
            return true;
        if (Focusable)
            return false;
        return child && child->focusLeft();
    }

    bool ControlContainer::focusRight() {
        if (__super::focusRight())
            return true;
        if (Focusable)
            return false;
        return child && child->focusRight();
    }

    void ControlContainer::dispatchContextChanged() {
        __super::dispatchContextChanged();
        if (child)
            child->dispatchContextChanged();
    }

    void ControlContainer::onMeasure(float parentWidth, float parentHeight) {
        if (child) {
            child->measure(
                PreferredSize.width >= 0 ? (float)PreferredSize.width : parentWidth,
                PreferredSize.height >= 0 ? (float)PreferredSize.height : parentHeight
            );
        }

        if (PreferredSize.width == PreferredSize::Width::WRAP) {
            if (child) {
                measuredSize.width = child->MeasuredSize.width;
            } else {
                measuredSize.width = 0;
            }
        } else if (PreferredSize.width != PreferredSize::Width::FILL) {
            measuredSize.width = (float)PreferredSize.width;
        }

        if (PreferredSize.height == PreferredSize::Height::WRAP) {
            if (child) {
                measuredSize.height = child->MeasuredSize.height;
            } else {
                measuredSize.height = 0;
            }
        } else if (PreferredSize.height != PreferredSize::Height::FILL) {
            measuredSize.height = (float)PreferredSize.height;
        }
    }

    bool ControlContainer::dispatchKeyEvent(const KeyEventArgs& event) {
        if (child && child->dispatchKeyEvent(event))
            return true;
        return __super::dispatchKeyEvent(event);
    }

    bool ControlContainer::dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
        if (child
            && (capturedChild || child->canReceiveEvent(event))
            && child->dispatchMouseButtonEvent(event.translate(-child->Position.x, -child->Position.y, true)))
            return true;
        return __super::dispatchMouseButtonEvent(event);
    }

    bool ControlContainer::dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
        if (child) {
            if (capturedChild || child->canReceiveEvent(event)) {
                previousReceiver = true;
                if (child->dispatchMouseMotionEvent(event.translate(-child->Position.x, -child->Position.y, true)))
                    return true;
            } else if (previousReceiver) {
                previousReceiver = false;
                if (child->dispatchMouseMotionEvent(event.translate(-child->Position.x, -child->Position.y, false)))
                    return true;
            }
        }
        return __super::dispatchMouseMotionEvent(event);
    }

    bool ControlContainer::dispatchMouseWheelEvent(const MouseWheelEventArgs& event) {
        if (child && child->canReceiveEvent(event) && child->dispatchMouseWheelEvent(event.translate(-child->Position.x, -child->Position.y)))
            return true;
        return __super::dispatchMouseWheelEvent(event);
    }

    Control* ControlContainer::find(const String& name) {
        if (this->Name && this->Name->operator==(name))
            return this;
        if (child)
            return child->find(name);
        return nullptr;
    }
}