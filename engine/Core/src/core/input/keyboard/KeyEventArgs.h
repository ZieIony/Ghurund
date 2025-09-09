#pragma once

#include "core/input/InputEventArgs.h"

namespace Ghurund::Core {
	enum class KeyAction {
		PRESSED, DOWN, RELEASED, CHAR
	};

	class KeyEventArgs:public InputEventArgs {
	private:
		KeyAction action;
		uint8_t keyCode;
		uint64_t pressedDuration;

	public:
		KeyEventArgs(KeyAction action, uint8_t keyCode, uint64_t pressedDuration, uint64_t time):
			InputEventArgs(time),
			action(action),
			keyCode(keyCode),
			pressedDuration(pressedDuration) {
		}

		inline KeyAction getAction() const {
			return action;
		}

		__declspec(property(get = getAction)) KeyAction Action;

		inline uint8_t getKeyCode() const {
			return keyCode;
		}

		__declspec(property(get = getKeyCode)) uint8_t KeyCode;

		inline uint64_t getPressedDurationMs() const {
			return pressedDuration;
		}

		__declspec(property(get = getPressedDurationMs)) uint64_t PressedDurationMs;
	};
}