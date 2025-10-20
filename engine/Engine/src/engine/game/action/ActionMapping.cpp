#include "ghepch.h"
#include "ActionMapping.h"

#include "core/reflection/StandardTypes.h"

namespace Ghurund::Engine {
	bool ActionMapping::onGamepadButtonEvent(const GamepadButtonEventArgs& event) {
		gamepadButtonActions.queryEventDispatch(
			event.Gamepad,
			event.Button,
			event.Action != GamepadButtonAction::RELEASED,
			event.TimeMs,
			dispatchTasks
		);
		return true;
	}

	bool ActionMapping::onGamepadTriggerEvent(const GamepadTriggerEventArgs& event) {
		gamepadTriggerActions.queryEventDispatch(
			event.Gamepad,
			event.Trigger,
			event.Value,
			event.TimeMs,
			dispatchTasks
		);
		return true;
	}

	bool ActionMapping::onGamepadStickEvent(const GamepadStickEventArgs& event) {
		gamepadStickActions.queryEventDispatch(
			event.Gamepad,
			event.Stick,
			event.Point,
			event.TimeMs,
			dispatchTasks
		);
		return true;
	}

	bool ActionMapping::onKeyEvent(const KeyEventArgs& event) {
		keyActions.queryEventDispatch(event.KeyCode, event.Action != KeyAction::RELEASED, event.TimeMs, dispatchTasks);
		return true;
	}

	bool ActionMapping::onMouseButtonEvent(const MouseButtonEventArgs& event) {
		mouseButtonActions.queryEventDispatch(
			event.Button,
			event.Action != MouseButtonAction::RELEASED,
			event.TimeMs,
			dispatchTasks
		);
		return true;
	}

	bool ActionMapping::onMouseMotionEvent(const MouseMotionEventArgs& event) {
		/*if (mouseMotionAction != nullptr) {
			mouseMotionAction->dispatchEvent(event.Delta, event.TimeMs);
			return true;
		}*/
		return false;
	}

	bool ActionMapping::onMouseWheelEvent(const MouseWheelEventArgs& event) {
		mouseWheelActions.queryEventDispatch(
			event.Wheel,
			(float)event.Delta,
			event.TimeMs,
			dispatchTasks
		);
		return true;
	}

	void ActionMapping::clear() {
		mouseButtonActions.clear();
		gamepadButtonActions.clear();
		gamepadTriggerActions.clear();
		gamepadStickActions.clear();
		keyActions.clear();
		delete mouseMotionAction;
		mouseMotionAction = nullptr;
	}
}