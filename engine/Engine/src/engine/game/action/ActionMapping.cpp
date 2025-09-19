#include "ghepch.h"
#include "ActionMapping.h"

#include "core/reflection/StandardTypes.h"

namespace Ghurund::Engine {
	bool ActionMapping::onGamepadButtonEvent(const GamepadButtonEventArgs& event) {
		auto it = gamepadActions[event.Gamepad].buttonActions.find(event.Button.Value);
		if (it != gamepadActions[event.Gamepad].buttonActions.end()) {
			it->value->dispatchEvent(event.Action != GamepadButtonAction::RELEASED, event.TimeMs);
			return true;
		}
		return false;
	}

	bool ActionMapping::onGamepadTriggerEvent(const GamepadTriggerEventArgs& event) {
		auto it = gamepadActions[event.Gamepad].triggerActions.find(event.Trigger);
		if (it != gamepadActions[event.Gamepad].triggerActions.end()) {
			it->value->dispatchEvent(event.Value, event.TimeMs);
			return true;
		}
		return false;
	}

	bool ActionMapping::onGamepadStickEvent(const GamepadStickEventArgs& event) {
		auto it = gamepadActions[event.Gamepad].stickActions.find(event.Stick);
		if (it != gamepadActions[event.Gamepad].stickActions.end()) {
			it->value->dispatchEvent(event.Point, event.TimeMs);
			return true;
		}
		return false;
	}

	bool ActionMapping::onKeyEvent(const KeyEventArgs& event) {
		auto it = keyActions.find(toupper(event.KeyCode));
		if (it != keyActions.end()) {
			it->value->dispatchEvent(event.Action != KeyAction::RELEASED, event.TimeMs);
			return true;
		}
		return false;
	}

	bool ActionMapping::onMouseButtonEvent(const MouseButtonEventArgs& event) {
		auto it = mouseButtonActions.find(event.Button);
		if (it != mouseButtonActions.end()) {
			it->value->dispatchEvent(event.Action != MouseButtonAction::RELEASED, event.TimeMs);
			return true;
		}
		return false;
	}

	bool ActionMapping::onMouseMotionEvent(const MouseMotionEventArgs& event) {
		if (mouseMotionAction != nullptr) {
			mouseMotionAction->dispatchEvent(event.Delta, event.TimeMs);
			return true;
		}
		return false;
	}

	bool ActionMapping::onMouseWheelEvent(const MouseWheelEventArgs& event) {
		auto it = mouseWheelActions.find(event.Wheel);
		if (it != mouseWheelActions.end()) {
			it->value->dispatchEvent(event.Delta, event.TimeMs);
			return true;
		}
		return false;
	}

	void ActionMapping::clear() {
		mouseButtonActions.clear();
		for (size_t i = 0; i < gamepadActions.Size; i++)
			gamepadActions[i].clear();
		keyActions.clear();
		delete mouseMotionAction;
		mouseMotionAction = nullptr;
	}
}