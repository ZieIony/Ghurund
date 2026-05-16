#pragma once

#include <cstdint>

namespace Ghurund::Engine {
	enum class DrawOrder:int8_t {
		BACK_TO_FRONT = -1, FRONT_TO_BACK = 1
	};

	class DrawGroup {
	private:
		uint32_t order;
		DrawOrder drawOrder;

	public:
		static inline uint32_t DEFAULT_GROUP_ORDER = 0;

		DrawGroup(uint32_t order = DEFAULT_GROUP_ORDER, DrawOrder drawOrder = DrawOrder::FRONT_TO_BACK):order(order), drawOrder(drawOrder) {}

		DrawGroup(const DrawGroup& other):order(other.order), drawOrder(other.drawOrder) {}

		DrawGroup(DrawGroup&& other) noexcept:order(other.order), drawOrder(other.drawOrder) {}

		inline uint32_t getGroupOrder() const {
			return order;
		}

		__declspec(property(get = getGroupOrder)) uint32_t GroupOrder;

		inline DrawOrder getDrawOrder() const {
			return drawOrder;
		}

		__declspec(property(get = getDrawOrder)) DrawOrder DrawOrder;

		inline DrawGroup operator=(const DrawGroup& other) {
			order = other.order;
			drawOrder = other.drawOrder;
			return *this;
		}

		inline DrawGroup operator=(DrawGroup&& other) noexcept {
			order = other.order;
			drawOrder = other.drawOrder;
			return *this;
		}

		constexpr auto operator<=>(const DrawGroup& other) const {
			return order <=> other.order;
		}
	};
}
