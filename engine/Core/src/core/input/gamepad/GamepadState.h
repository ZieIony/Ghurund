#pragma once

#include <xinput.h>
#include <cstdint>

#include <core/math/Point.h>
#include "GamepadButton.h"

namespace Ghurund::Core {
	class GamepadState {
	private:
		uint16_t buttons;
		FloatPoint leftStick, rightStick;
		float leftTrigger, rightTrigger;

		static inline float shortToFloat(SHORT s) {
			return (((int16_t)s) + 32768) / (float)(32767 + 32768) * 2 - 1;
		}

	public:
		GamepadState(XINPUT_GAMEPAD state):
			buttons(state.wButtons),
			leftTrigger(state.bLeftTrigger / 255.0f),
			rightTrigger(state.bRightTrigger / 255.0f),
			leftStick(FloatPoint{ shortToFloat(state.sThumbLX), shortToFloat(state.sThumbLY) }),
			rightStick(FloatPoint{ shortToFloat(state.sThumbRX), shortToFloat(state.sThumbRY) }) {
		}

		inline bool isButtonDown(const GamepadButton& button) const {
			return buttons & button.Bitmask;
		}

		inline FloatPoint getLeftStick() const {
			return leftStick;
		}

		__declspec(property(get = getLeftStick)) FloatPoint LeftStick;

		inline FloatPoint getRightStick() const {
			return rightStick;
		}

		__declspec(property(get = getRightStick)) FloatPoint RightStick;

		inline float getLeftTrigger() const {
			return leftTrigger;
		}

		__declspec(property(get = getLeftTrigger)) float LeftTrigger;

		inline float getRightTrigger() const {
			return rightTrigger;
		}

		__declspec(property(get = getRightTrigger)) float RightTrigger;
	};
}