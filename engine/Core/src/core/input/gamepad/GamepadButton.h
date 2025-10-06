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

		GamepadButton(GamepadButtonEnum value, const char* name, uint16_t bitmask):Enum<GamepadButtonEnum, GamepadButton>(value, name), bitmask(bitmask) {}

	public:
		static const GamepadButton DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT, START, BACK, LEFT_STICK, RIGHT_STICK, LEFT_SHOULDER, RIGHT_SHOULDER, A, B, X, Y;

		GamepadButton(const GamepadButton& other):Enum(other), bitmask(other.bitmask) {}

		GamepadButton(GamepadButton&& other) noexcept:Enum(other), bitmask(other.bitmask) {}

		inline uint16_t getBitmask() const {
			return bitmask;
		}

		__declspec(property(get = getBitmask)) uint16_t Bitmask;

		inline GamepadButton& operator=(const GamepadButton& other) {
			if (this == &other)
				return *this;
			__super::operator=(other);
			bitmask = other.bitmask;
			return *this;
		}

		inline GamepadButton& operator=(GamepadButton&& other) noexcept {
			if (this == &other)
				return *this;
			__super::operator=(std::move(other));
			bitmask = other.bitmask;
			return *this;
		}
	};
}