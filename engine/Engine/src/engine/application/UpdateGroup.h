#pragma once

#include <cstdint>
#include <compare>

namespace Ghurund::Engine {
	class UpdateGroup {
	private:
		int32_t order = DEFAULT_GROUP_ORDER;

	public:
		static inline int32_t DEFAULT_GROUP_ORDER = 0;

		UpdateGroup(int32_t order = DEFAULT_GROUP_ORDER):order(order) {}

		UpdateGroup(const UpdateGroup& other):order(other.order) {}

		UpdateGroup(UpdateGroup&& other) noexcept:order(other.order) {}

		inline int32_t getGroupOrder() const {
			return order;
		}

		__declspec(property(get = getGroupOrder)) int32_t GroupOrder;

		inline UpdateGroup operator=(const UpdateGroup& other) {
			order = other.order;
			return *this;
		}

		inline UpdateGroup operator=(UpdateGroup&& other) noexcept {
			order = other.order;
			return *this;
		}

		constexpr std::strong_ordering operator<=>(const UpdateGroup& other) const noexcept {
			return order <=> other.order;
		}
	};
}
