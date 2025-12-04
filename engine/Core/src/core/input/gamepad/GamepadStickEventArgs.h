#pragma once

#include "core/input/InputEventArgs.h"

#include <cstdint>
#include <DirectXMath.h>

namespace Ghurund::Core {
	using namespace ::DirectX;

	enum class GamepadStick {
		LEFT, RIGHT
	};

	class GamepadStickEventArgs:public InputEventArgs {
	private:
		uint8_t gamepad;
		GamepadStick stick;
		XMFLOAT2 point;

	public:
		GamepadStickEventArgs(
			uint8_t gamepad,
			GamepadStick stick,
			XMFLOAT2 point,
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

		inline const XMFLOAT2& getPoint() const {
			return point;
		}

		__declspec(property(get = getPoint)) const XMFLOAT2& Point;
	};
}