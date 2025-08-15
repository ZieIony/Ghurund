#pragma once

#include <stdint.h>
#include <Windows.h>

namespace Ghurund::Core {
	class WindowDecorationMetrics {
	private:
		uint32_t left, top, right, bottom;

	public:
		void init(HWND handle);

		inline uint32_t getLeft() const {
			return left;
		}

		__declspec(property(get = getLeft)) uint32_t Left;

		inline uint32_t getTop() const {
			return top;
		}

		__declspec(property(get = getTop)) uint32_t Top;

		inline uint32_t getRight() const {
			return right;
		}

		__declspec(property(get = getRight)) uint32_t Right;

		inline uint32_t getBottom() const {
			return bottom;
		}

		__declspec(property(get = getBottom)) uint32_t Bottom;

		inline uint32_t getHorizontal() const {
			return left + right;
		}

		__declspec(property(get = getHorizontal)) uint32_t Horizontal;

		inline uint32_t getVertical() const {
			return top + bottom;
		}

		__declspec(property(get = getVertical)) uint32_t Vertical;
	};
}