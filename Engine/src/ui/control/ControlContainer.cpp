#include "ControlContainer.h"

namespace Ghurund::UI {
    bool ControlContainer::focusNext() {
        if (!Focused && Focusable && Parent) {
            Parent->setFocus(this);
            onStateChanged();
            return true;
        }
        if (!child || !child->Enabled || !child->Visible || Focusable)
            return false;
        return child->focusNext();
    }

    bool ControlContainer::focusPrevious() {
        if (!Focused && Focusable && Parent) {
            Parent->setFocus(this);
            onStateChanged();
            return true;
        }
        if (!child || !child->Enabled || !child->Visible || Focusable)
            return false;
        return child->focusPrevious();
    }

    void ControlContainer::onMeasure(float parentWidth, float parentHeight) {
        if (child) {
            child->measure(
                PreferredSize.width >= 0 ? PreferredSize.width : parentWidth,
                PreferredSize.height >= 0 ? PreferredSize.height : parentHeight
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
        if (child) {
            if (childCaptured) {
                bool result = child->dispatchMouseButtonEvent(event.translate(-child->Position.x, -child->Position.y));
                if (event.Action == MouseAction::UP)
                    childCaptured = false;
                if (result)
                    return true;
            }
            if (child->canReceiveEvent(event) && child->dispatchMouseButtonEvent(event.translate(-child->Position.x, -child->Position.y))) {
                if (event.Action == MouseAction::DOWN)
                    childCaptured = true;
                return true;
            }
        }
        return __super::dispatchMouseButtonEvent(event);
    }

    bool ControlContainer::dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
        if (child) {
            if (childCaptured || child->canReceiveEvent(event)) {
                previousReceiver = true;
                if (child->dispatchMouseMotionEvent(event.translate(-child->Position.x, -child->Position.y)))
                    return true;
            } else if (previousReceiver) {
                previousReceiver = false;
                if (child->dispatchMouseMotionEvent(event.translate(-child->Position.x, -child->Position.y)))
                    return true;
            }
        }
        return __super::dispatchMouseMotionEvent(event);
    }

    bool ControlContainer::dispatchMouseWheelEvent(const MouseWheelEventArgs& event) {
        if ((childCaptured || child && child->canReceiveEvent(event)) &&
            child->dispatchMouseWheelEvent(event.translate(-child->Position.x, -child->Position.y)))
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