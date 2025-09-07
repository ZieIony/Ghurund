#pragma once

#include <cstdint>

#include "core/input/InputEventArgs.h"

namespace Ghurund::Core {
	enum class GamepadTrigger {
		LEFT, RIGHT
	};

	class GamepadTriggerEventArgs:public InputEventArgs {
	private:
		uint8_t gamepad;
		GamepadTrigger trigger;
		float value;

	public:
		GamepadTriggerEventArgs(
			uint8_t gamepad,
			GamepadTrigger trigger,
			float value,
			uint64_t time
		):InputEventArgs(time), gamepad(gamepad), trigger(trigger), value(value) {
		}

		inline uint8_t getGamepad() const {
			return gamepad;
		}

		__declspec(property(get = getGamepad)) uint8_t Gamepad;

		inline GamepadTrigger getTrigger() const {
			return trigger;
		}

		__declspec(property(get = getTrigger)) GamepadTrigger Trigger;

		inline float getValue() const {
			return value;
		}

		__declspec(property(get = getValue)) float Value;
	};
}