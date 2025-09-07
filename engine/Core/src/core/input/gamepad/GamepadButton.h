#pragma once

#include <cstdint>

#include "core/Enum.h"

namespace Ghurund::Core {
	enum class GamepadButtonEnum {
		DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT,
		START, BACK,
		LEFT_STICK, RIGHT_STICK,
		LEFT_SHOULDER, RIGHT_SHOULDER,
		A, B, X, Y
	};

	class GamepadButton:public Enum<GamepadButtonEnum, GamepadButton> {
	private:
		uint16_t bitmask;

	public:
		static const GamepadButton DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT, START, BACK, LEFT_STICK, RIGHT_STICK, LEFT_SHOULDER, RIGHT_SHOULDER, A, B, X, Y;

		GamepadButton(GamepadButtonEnum value, const char* name, uint16_t bitmask):Enum<GamepadButtonEnum, GamepadButton>(value, name), bitmask(bitmask) {
		}

		inline uint16_t getBitmask() const {
			return bitmask;
		}

		__declspec(property(get = getBitmask)) uint16_t Bitmask;
	};
}