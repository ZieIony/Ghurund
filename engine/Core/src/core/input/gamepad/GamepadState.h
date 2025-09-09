#pragma once

#include <cstdint>

#include <core/math/Point.h>
#include "GamepadButton.h"

namespace Ghurund::Core {
	class GamepadState {
	private:
		uint16_t buttons;
		FloatPoint leftStick, rightStick;
		float leftTrigger, rightTrigger;

	public:
		GamepadState(
			uint16_t buttons,
			FloatPoint leftStick, FloatPoint rightStick,
			float leftTrigger, float rightTrigger
		):
			buttons(buttons),
			leftTrigger(leftTrigger), rightTrigger(leftTrigger),
			leftStick(leftStick), rightStick(leftStick) {
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