#pragma once

#include <cstdint>

namespace Ghurund::Core {
	struct GamepadButtonState {
		bool isDown;
		uint64_t pressedTime;
	};
}