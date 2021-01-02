#include "HoverableView.h"

namespace Ghurund::UI {
    bool HoverableView::onMouseMotionEvent(const Input::MouseMotionEventArgs& event) {
        bool in = event.Position.x >= 0 && event.Position.x < Size.width&&
            event.Position.y >= 0 && event.Position.y < Size.height;
        if (in && !hovered) {
            hovered = true;
            onStateChanged();
        } else if (!in && hovered) {
            hovered = false;
            onStateChanged();
        }

        return __super::onMouseMotionEvent(event);
    }
}
