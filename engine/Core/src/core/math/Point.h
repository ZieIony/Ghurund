#pragma once

#include "Common.h"

#include <compare>
#include <format>

namespace Ghurund::Core {
	template<typename T>
	struct BasePoint {
		T x, y;

		auto operator<=>(const BasePoint& other) const = default;
	};

	typedef BasePoint<int32_t> IntPoint;
	typedef BasePoint<float> FloatPoint;
}

template <typename T>
struct std::formatter<Ghurund::Core::BasePoint<T>, char>:std::formatter<const char*, char> {
	template <typename FormatContext>
	auto format(const Ghurund::Core::BasePoint<T>& obj, FormatContext& ctx) const {
		return format_to(ctx.out(), "[{}, {}]", obj.x, obj.y);
	}
};

template <typename T>
struct std::formatter<Ghurund::Core::BasePoint<T>, wchar_t>:std::formatter<const wchar_t*, wchar_t> {
	template <typename FormatContext>
	auto format(const Ghurund::Core::BasePoint<T>& obj, FormatContext& ctx) const {
		return format_to(ctx.out(), L"[{}, {}]", obj.x, obj.y);
	}
};