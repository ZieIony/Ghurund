#pragma once

#include "GamepadButton.h"

#include <cstdint>
#include <DirectXMath.h>

namespace Ghurund::Core {
	using namespace ::DirectX;

	class GamepadState {
	private:
		uint16_t buttons;
		XMFLOAT2 leftStick, rightStick;
		float leftTrigger, rightTrigger;

	public:
		GamepadState(
			uint16_t buttons,
			const XMFLOAT2& leftStick, const XMFLOAT2& rightStick,
			float leftTrigger, float rightTrigger
		):
			buttons(buttons),
			leftTrigger(leftTrigger), rightTrigger(leftTrigger),
			leftStick(leftStick), rightStick(leftStick) {
		}

		inline bool isButtonDown(const GamepadButton& button) const {
			return buttons & button.Bitmask;
		}

		inline const XMFLOAT2& getLeftStick() const {
			return leftStick;
		}

		__declspec(property(get = getLeftStick)) const XMFLOAT2& LeftStick;

		inline const XMFLOAT2& getRightStick() const {
			return rightStick;
		}

		__declspec(property(get = getRightStick)) const XMFLOAT2& RightStick;

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