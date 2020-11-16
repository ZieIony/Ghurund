#include "HoverableView.h"

namespace Ghurund::UI {
    bool HoverableView::onMouseMotionEvent(const MouseMotionEventArgs& event) {
        if (__super::onMouseMotionEvent(event))
            return true;

        bool in = event.Position.x >= 0 && event.Position.x < Size.width&&
            event.Position.y >= 0 && event.Position.y < Size.height;
        if (in && !hovered) {
            hovered = true;
            onStateChanged();
            return true;
        } else if (!in && hovered) {
            hovered = false;
            onStateChanged();
            return true;
        }

        return false;
    }
}
