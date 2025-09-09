#pragma once

#include <cstdint>

namespace Ghurund::Core {
	struct KeyState {
		bool isDown;
		uint64_t pressedTime;
	};
}