#include "ghcpch.h"
#include "GamepadInput.h"

#include <xinput.h>

namespace Ghurund::Core {
    GamepadState* GamepadInput::getGamepadState(uint8_t index) {
        DWORD dwResult;
        XINPUT_STATE state = {};

        dwResult = XInputGetState(index, &state);

        if (dwResult == ERROR_SUCCESS) {
            auto gamepad = state.Gamepad;
            return ghnew GamepadState(
                (uint16_t)gamepad.wButtons,
                FloatPoint{ shortToFloat(gamepad.sThumbLX), shortToFloat(gamepad.sThumbLY) },
                FloatPoint{ shortToFloat(gamepad.sThumbRX), shortToFloat(gamepad.sThumbRY) },
                gamepad.bLeftTrigger / 255.0f,
                gamepad.bRightTrigger / 255.0f
            );
        } else {
            return nullptr;
        }
    }
	
	const uint8_t GamepadInput::MAX_GAMEPADS = XUSER_MAX_COUNT;

	void GamepadInput::dispatchEvents(uint64_t time, EventConsumer& consumer) {
		for (uint8_t gamepadIndex = 0; gamepadIndex < MAX_GAMEPADS; gamepadIndex++) {
			auto state = getGamepadState(gamepadIndex);
			if (state) {
				for (size_t j = 0; j < gamepadButtonState.Size; j++) {
					auto& gamepadButton = GamepadButton::VALUES[j];
					auto& buttonState = gamepadButtonState[j];
					bool down = state->isButtonDown(gamepadButton);
					if (down && !buttonState.isDown) {
						auto event = GamepadButtonEventArgs(
							gamepadIndex,
							GamepadButtonAction::PRESSED,
							gamepadButton,
							0,
							time
						);
						consumer.dispatchGamepadButtonEvent(event);
						buttonState.isDown = true;
						buttonState.pressedTime = time;
					}
					if (!down && buttonState.isDown) {
						auto event = GamepadButtonEventArgs(
							gamepadIndex,
							GamepadButtonAction::RELEASED,
							gamepadButton,
							time - buttonState.pressedTime,
							time
						);
						consumer.dispatchGamepadButtonEvent(event);
						buttonState.isDown = false;
					}
					if (down && buttonState.isDown) {
						auto event = GamepadButtonEventArgs(
							gamepadIndex,
							GamepadButtonAction::DOWN,
							gamepadButton,
							time - buttonState.pressedTime,
							time
						);
						consumer.dispatchGamepadButtonEvent(event);
					}
				}
				consumer.dispatchGamepadStickEvent(GamepadStickEventArgs(gamepadIndex, GamepadStick::LEFT, state->LeftStick, time));
				consumer.dispatchGamepadStickEvent(GamepadStickEventArgs(gamepadIndex, GamepadStick::RIGHT, state->RightStick, time));
				consumer.dispatchGamepadTriggerEvent(GamepadTriggerEventArgs(gamepadIndex, GamepadTrigger::LEFT, state->LeftTrigger, time));
				consumer.dispatchGamepadTriggerEvent(GamepadTriggerEventArgs(gamepadIndex, GamepadTrigger::RIGHT, state->RightTrigger, time));
				delete state;
			}
		}
	}
}