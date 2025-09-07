#pragma once

#include <cstdint>

#include "GamepadState.h"

namespace Ghurund::Core {
	class GamepadInput {
	private:
		bool enabled = true;

	public:
		uint8_t getMaxGamepads() const;

		__declspec(property(get = getMaxGamepads)) uint8_t MaxGamepads;

		GamepadState* getState(uint8_t index);

		void setIsEnabled(bool enabled);

		inline bool getIsEnabled() const {
			return enabled;
		}

		__declspec(property(get = getIsEnabled, put = setIsEnabled)) bool IsEnabled;
	};
}