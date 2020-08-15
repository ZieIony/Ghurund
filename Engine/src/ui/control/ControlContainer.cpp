#include "ControlContainer.h"

namespace Ghurund::UI {
    void ControlContainer::measure() {
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
        if (child->Visible && child->Enabled &&
            event.Position.x >= child->Position.x && event.Position.x <= child->Position.x + child->Size.x &&
            event.Position.y >= child->Position.y && event.Position.y <= child->Position.y + child->Size.y) {
            XMINT2 childEventPos = { (int32_t)(event.Position.x - child->Position.x), (int32_t)(event.Position.y - child->Position.y) };
            MouseButtonEventArgs childEvent = MouseButtonEventArgs(childEventPos, event.Action, event.Button, event.Time);
            if (child->dispatchMouseButtonEvent(childEvent))
                return true;
        }
        return __super::dispatchMouseButtonEvent(event);
    }
}