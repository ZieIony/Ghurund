#pragma once

#include <cstdint>

namespace Ghurund::Core {
	class KeyboardKey {
	private:
		uint8_t code;

	public:
		KeyboardKey(uint8_t code):code(toupper(code)) {}

		KeyboardKey(const KeyboardKey& other):code(other.code) {}

		KeyboardKey(KeyboardKey&& other) noexcept:code(other.code) {}

		inline uint8_t getCode() const {
			return code;
		}

		__declspec(property(get = getCode)) uint8_t Code;

		inline KeyboardKey& operator=(const KeyboardKey& other) {
			code = other.code;
			return *this;
		}

		inline KeyboardKey& operator=(KeyboardKey&& other) noexcept {
			code = other.code;
			return *this;
		}

		inline auto operator<=>(const KeyboardKey& other) const {
			return code <=> other.code;
		}
	};
}