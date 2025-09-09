#pragma once

#include <cstdint>

namespace Ghurund::Core {
	struct MouseButtonState {
		bool isDown;
		uint64_t pressedTime;
	};
}