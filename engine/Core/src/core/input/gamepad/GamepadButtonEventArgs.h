#pragma once

#include <cstdint>

#include "core/input/InputEventArgs.h"
#include "GamepadButton.h"

namespace Ghurund::Core {
	enum class GamepadButtonAction {
		PRESSED, DOWN, RELEASED
	};

	class GamepadButtonEventArgs:public InputEventArgs {
	private:
		uint8_t gamepad;
		GamepadButtonAction action;
		const GamepadButton& button;
		uint64_t pressedDuration;

	public:
		GamepadButtonEventArgs(
			uint8_t gamepad,
			GamepadButtonAction action,
			const GamepadButton& button,
			uint64_t pressedDuration,
			uint64_t time
		):InputEventArgs(time), gamepad(gamepad), action(action), button(button), pressedDuration(pressedDuration) {
		}

		inline uint8_t getGamepad() const {
			return gamepad;
		}

		__declspec(property(get = getGamepad)) uint8_t Gamepad;

		inline GamepadButtonAction getAction() const {
			return action;
		}

		__declspec(property(get = getAction)) GamepadButtonAction Action;

		inline const GamepadButton& getKeyCode() const {
			return button;
		}

		__declspec(property(get = getKeyCode)) const GamepadButton& Button;

		inline uint64_t getPressedDurationMs() const {
			return pressedDuration;
		}

		__declspec(property(get = getPressedDurationMs)) uint64_t PressedDurationMs;
	};
}