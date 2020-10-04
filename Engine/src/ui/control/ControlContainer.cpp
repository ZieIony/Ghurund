#include "ControlContainer.h"

namespace Ghurund::UI {
    void ControlContainer::onMeasure(float parentWidth, float parentHeight) {
        if (child) {
            child->measure(
                preferredSize.width >= 0 ? preferredSize.width : parentWidth,
                preferredSize.height >= 0 ? preferredSize.height : parentHeight
            );
        }

        if (preferredSize.width == PreferredSize::Width::WRAP) {
            if (child) {
                measuredSize.width = child->MeasuredSize.width;
            } else {
                measuredSize.width = 0;
            }
        } else if (preferredSize.width != PreferredSize::Width::FILL) {
            measuredSize.width = (float)preferredSize.width;
        }

        if (preferredSize.height == PreferredSize::Height::WRAP) {
            if (child) {
                measuredSize.height = child->MeasuredSize.height;
            } else {
                measuredSize.height = 0;
            }
        } else if (preferredSize.height != PreferredSize::Height::FILL) {
            measuredSize.height = (float)preferredSize.height;
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
        if (this->name && this->name->operator==(name))
            return this;
        if (child)
            return child->find(name);
        return nullptr;
    }
}