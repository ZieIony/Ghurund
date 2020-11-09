#include "ClickableView.h"

namespace Ghurund::UI {
    bool ClickableView::onKeyEvent(const KeyEventArgs& event) {
        if (event.Key == VK_SPACE || event.Key == VK_RETURN) {
            if (event.Action == KeyAction::DOWN) {
                buttons[MouseButton::VIRTUAL] = true;
                onStateChanged();
                onPressed(MousePressedEventArgs({ (int32_t)(Size.width / 2), (int32_t)(Size.height / 2) }, MouseButton::VIRTUAL, event.Time));
                return true;
            } else if (event.Action == KeyAction::UP) {
                buttons[MouseButton::VIRTUAL] = false;
                onStateChanged();
                onClicked(MouseClickedEventArgs({ (int32_t)(Size.width / 2), (int32_t)(Size.height / 2) }, MouseButton::VIRTUAL, event.Time));
                return true;
            }
        }
        return false;
    }
    
    bool ClickableView::onMouseButtonEvent(const MouseButtonEventArgs& event) {
        __super::onMouseButtonEvent(event);
        bool result = false;
        if (event.Action == MouseAction::DOWN && !buttons[event.Button]) {
            buttons[event.Button] = true;
            onStateChanged();
            onPressed(MousePressedEventArgs(event.Position, event.Button, event.TimeMs));
            return true;
        } else if (event.Action == MouseAction::UP && buttons[event.Button]) {
            buttons[event.Button] = false;
            onStateChanged();
            return onClicked(MouseClickedEventArgs(event.Position, event.Button, event.TimeMs));
        }
        return false;
    }
}
