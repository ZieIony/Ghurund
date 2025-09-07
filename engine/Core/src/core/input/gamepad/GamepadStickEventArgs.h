#pragma once

#include <cstdint>

#include "core/input/InputEventArgs.h"
#include <core/math/Point.h>

namespace Ghurund::Core {
	enum class GamepadStick {
		LEFT, RIGHT
	};

	class GamepadStickEventArgs:public InputEventArgs {
	private:
		uint8_t gamepad;
		GamepadStick stick;
		FloatPoint point;

	public:
		GamepadStickEventArgs(
			uint8_t gamepad,
			GamepadStick stick,
			FloatPoint point,
			uint64_t time
		):InputEventArgs(time), gamepad(gamepad), stick(stick), point(point) {
		}

		inline uint8_t getGamepad() const {
			return gamepad;
		}

		__declspec(property(get = getGamepad)) uint8_t Gamepad;

		inline GamepadStick getStick() const {
			return stick;
		}

		__declspec(property(get = getStick)) GamepadStick Stick;

		inline FloatPoint getPoint() const {
			return point;
		}

		__declspec(property(get = getPoint)) FloatPoint Point;
	};
}