#include "ghuipch.h"
#include "ClickableControl.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& ClickableControl::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<ClickableControl>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<ClickableControl>(NAMESPACE_NAME, GH_STRINGIFY(ClickableControl))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool ClickableControl::onKeyEvent(const KeyEventArgs& event) {
        if (event.Key == VK_SPACE || event.Key == VK_RETURN) {
            if (event.Action == KeyAction::DOWN) {
                buttons[MouseButton::VIRTUAL] = true;
                dispatchStateChanged();
                return pressed(MousePressedEventArgs({ (int32_t)(Size.Width / 2), (int32_t)(Size.Height / 2) }, MouseButton::VIRTUAL, event.TimeMs));
            } else if (event.Action == KeyAction::UP) {
                buttons[MouseButton::VIRTUAL] = false;
                dispatchStateChanged();
                return clicked(MouseClickedEventArgs({ (int32_t)(Size.Width / 2), (int32_t)(Size.Height / 2) }, MouseButton::VIRTUAL, event.TimeMs, true));
            }
        }
        return false;
    }

    bool ClickableControl::onMouseMotionEvent(const MouseMotionEventArgs& event) {
        bool in = event.Position.x >= 0 && event.Position.x < Size.Width&&
            event.Position.y >= 0 && event.Position.y < Size.Height;
        if (in && !hovered) {
            hovered = true;
            dispatchStateChanged();
        } else if (!in && hovered) {
            hovered = false;
            dispatchStateChanged();
        }

        return hovered;
    }

    bool ClickableControl::onMouseButtonEvent(const MouseButtonEventArgs& event) {
        bool result = __super::onMouseButtonEvent(event);
        if (event.Action == MouseAction::DOWN && !buttons[event.Button]) {
            buttons[event.Button] = true;
            Parent->CapturedChild = this;
            dispatchStateChanged();
            return pressed(MousePressedEventArgs(event.Position, event.Button, event.TimeMs)) || result;
        } else if (event.Action == MouseAction::UP && buttons[event.Button]) {
            buttons[event.Button] = false;
            Parent->CapturedChild = nullptr;
            dispatchStateChanged();
            return clicked(MouseClickedEventArgs(event.Position, event.Button, event.TimeMs, event.Inside)) || result;
        }
        return result;
    }
}
