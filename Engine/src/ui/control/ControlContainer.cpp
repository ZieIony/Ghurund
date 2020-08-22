#include "ControlContainer.h"

namespace Ghurund::UI {
    void ControlContainer::onMeasure() {
        if (child)
            child->measure();

        if (preferredSize.width == PreferredSize::Width::WRAP) {
            if (child) {
                measuredSize.x = child->MeasuredSize.x;
            } else {
                measuredSize.x = 0;
            }
        } else if (preferredSize.width != PreferredSize::Width::FILL) {
            measuredSize.x = (float)preferredSize.width;
        }

        if (preferredSize.height == PreferredSize::Height::WRAP) {
            if (child) {
                measuredSize.y = child->MeasuredSize.y;
            } else {
                measuredSize.y = 0;
            }
        } else if (preferredSize.height != PreferredSize::Height::FILL) {
            measuredSize.y = (float)preferredSize.height;
        }
    }

    bool ControlContainer::dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
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
        return __super::dispatchMouseButtonEvent(event);
    }

    bool ControlContainer::dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
        if (childCaptured || child->canReceiveEvent(event)) {
            previousReceiver = true;
            if (child->dispatchMouseMotionEvent(event.translate(-child->Position.x, -child->Position.y)))
                return true;
        }else if (previousReceiver) {
            previousReceiver = false;
            if (child->dispatchMouseMotionEvent(event.translate(-child->Position.x, -child->Position.y)))
                return true;
        }
        return __super::dispatchMouseMotionEvent(event);
    }

    bool ControlContainer::dispatchMouseWheelEvent(const MouseWheelEventArgs& event) {
        if ((childCaptured || child->canReceiveEvent(event)) &&
            child->dispatchMouseWheelEvent(event.translate(-child->Position.x, -child->Position.y)))
            return true;
        return __super::dispatchMouseWheelEvent(event);
    }

    Control* ControlContainer::find(const String& name) {
        if (this->name && name.operator==(this->name))
            return this;
        if (child)
            return child->find(name);
        return nullptr;
    }
}