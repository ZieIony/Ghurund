#include "ghuipch.h"
#include "InteractionHandler.h"

namespace Ghurund::UI {
	bool InteractionHandler::onKeyEvent(const KeyEventArgs& event) {
		if (event.Key == VK_SPACE || event.Key == VK_RETURN) {
			if (event.Action == KeyAction::DOWN) {
				buttons[MouseButton::VIRTUAL] = true;
				isPressed = buttons;
				return pressed(MousePressedEventArgs({ 0, 0 }, MouseButton::VIRTUAL, event.TimeMs));
			} else if (event.Action == KeyAction::UP) {
				buttons[MouseButton::VIRTUAL] = false;
				isPressed = buttons;
				return clicked(MouseClickedEventArgs({ 0, 0 }, MouseButton::VIRTUAL, event.TimeMs, true));
			}
		} else if (event.Key == VK_ESCAPE || isPressed) {
			buttons.clear();
			isPressed = false;
			return canceled();
		}
		return false;
	}

	bool InteractionHandler::onMouseButtonEvent(const MouseButtonEventArgs& event) {
		if (event.Action == MouseAction::DOWN && !buttons[event.Button]) {
			buttons[event.Button] = true;
			isPressed = buttons;
			return pressed(MousePressedEventArgs(event.Position, event.Button, event.TimeMs));
		} else if (event.Action == MouseAction::UP && buttons[event.Button]) {
			buttons[event.Button] = false;
			isPressed = buttons;
			return clicked(MouseClickedEventArgs(event.Position, event.Button, event.TimeMs, event.Inside));
		}
		return false;
	}

	bool InteractionHandler::onMouseMotionEvent(const MouseMotionEventArgs& event) {
		bool in = event.Position.x >= 0 && event.Position.x < owner.Size.Width &&
			event.Position.y >= 0 && event.Position.y < owner.Size.Height;
		if (in && !isHovered) {
			isHovered = true;
		} else if (!in && isHovered) {
			isHovered = false;
		}

		return isHovered;
	}
}