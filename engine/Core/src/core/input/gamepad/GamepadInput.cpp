#include "ghcpch.h"

#include <Windows.h>
#include <xinput.h>

namespace Ghurund::Core {
	uint8_t GamepadInput::getMaxGamepads() const {
		return XUSER_MAX_COUNT;
	}

	GamepadState* GamepadInput::getState(uint8_t index) {
		DWORD dwResult;
		XINPUT_STATE state = {};

		dwResult = XInputGetState(index, &state);

		if (dwResult == ERROR_SUCCESS) {
			return ghnew GamepadState(state.Gamepad);
		} else {
			return nullptr;
		}
	}
	
	void GamepadInput::setIsEnabled(bool enabled) {
		this->enabled = enabled;
		XInputEnable(enabled ? TRUE : FALSE);
	}
}