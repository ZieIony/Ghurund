#include "ghepch.h"
#include "ActionMapping.h"

#include "core/reflection/StandardTypes.h"

namespace Ghurund::Engine {
	bool ActionMapping::onGamepadButtonEvent(const GamepadButtonEventArgs& event) {
		auto it = gamepadButtonActions.find(event.Button.Value);
		if (it != gamepadButtonActions.end()) {
			if (event.Action == GamepadButtonAction::PRESSED) {
				it->value->dispatchStarted(1.0f);
			} else if (event.Action == GamepadButtonAction::DOWN) {
				it->value->dispatchInProgress(1.0f, event.PressedDurationMs);
			} else if (event.Action == GamepadButtonAction::RELEASED) {
				it->value->dispatchFinished(event.PressedDurationMs);
			}
			return true;
		}
		return false;
	}

	bool ActionMapping::onGamepadStickEvent(const GamepadStickEventArgs& event) {
		auto it = gamepadStickActions.find(event.Stick);
		if (it != gamepadStickActions.end()) {
			it->value->dispatchInProgress(event.Point, 0.0f);
			return true;
		}
		return false;
	}

	bool ActionMapping::onKeyEvent(const KeyEventArgs& event) {
		auto it = keyActions.find(event.KeyCode);
		if (it != keyActions.end()) {
			if (event.Action == KeyAction::PRESSED) {
				it->value->dispatchStarted(1.0f);
			} else if (event.Action == KeyAction::DOWN) {
				it->value->dispatchInProgress(1.0f, event.PressedDurationMs);
			} else if (event.Action == KeyAction::RELEASED) {
				it->value->dispatchFinished(event.PressedDurationMs);
			}
			return true;
		}
		return false;
	}
}