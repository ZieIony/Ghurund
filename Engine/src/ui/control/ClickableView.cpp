#include "ClickableView.h"

namespace Ghurund::UI {
    bool ClickableView::onKeyEvent(const KeyEventArgs& event) {
        if (event.Key == VK_SPACE || event.Key == VK_RETURN) {
            if (event.Action == KeyAction::DOWN) {
                buttons[MouseButton::VIRTUAL] = true;
                onStateChanged();
                onPressed(MousePressedEventArgs({ (int32_t)(Size.width / 2), (int32_t)(Size.height / 2) }, MouseButton::VIRTUAL, event.TimeMs));
                return true;
            } else if (event.Action == KeyAction::UP) {
                buttons[MouseButton::VIRTUAL] = false;
                onStateChanged();
                onClicked(MouseClickedEventArgs({ (int32_t)(Size.width / 2), (int32_t)(Size.height / 2) }, MouseButton::VIRTUAL, event.TimeMs, true));
                return true;
            }
        }
        return false;
    }

    bool ClickableView::onMouseMotionEvent(const Ghurund::Input::MouseMotionEventArgs& event) {
        bool in = event.Position.x >= 0 && event.Position.x < Size.width&&
            event.Position.y >= 0 && event.Position.y < Size.height;
        if (in && !hovered) {
            hovered = true;
            onStateChanged();
        } else if (!in && hovered) {
            hovered = false;
            onStateChanged();
        }

        return false;
    }

    bool ClickableView::onMouseButtonEvent(const MouseButtonEventArgs& event) {
        if (__super::onMouseButtonEvent(event))
            return true;
        if (event.Action == MouseAction::DOWN && !buttons[event.Button]) {
            buttons[event.Button] = true;
            setCapturedChild(this);
            onStateChanged();
            if (onPressed(MousePressedEventArgs(event.Position, event.Button, event.TimeMs)))
                return true;
        } else if (event.Action == MouseAction::UP && buttons[event.Button]) {
            buttons[event.Button] = false;
            setCapturedChild(nullptr);
            onStateChanged();
            if (onClicked(MouseClickedEventArgs(event.Position, event.Button, event.TimeMs, event.Inside)))
                return true;
        }
        return false;
    }
}
