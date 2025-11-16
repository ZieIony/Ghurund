#pragma once

#include <format>
#include <DirectXMath.h>

namespace Ghurund::Core {
	using namespace ::DirectX;

	inline XMFLOAT2 operator*(const XMFLOAT2& obj, float mul) {
		return { obj.x * mul, obj.y * mul };
	}

	inline XMINT2 operator*(const XMINT2& obj, float mul) {
		return { (int32_t)(obj.x * mul), (int32_t)(obj.y * mul) };
	}

	inline XMFLOAT2 operator+(const XMFLOAT2& obj, const XMFLOAT2& other) {
		return { obj.x + other.x, obj.y + other.y };
	}

	inline XMINT2 operator+(const XMINT2& obj, const XMINT2& other) {
		return { obj.x + other.x, obj.y + other.y };
	}

	inline XMFLOAT2 operator-(const XMFLOAT2& obj, const XMFLOAT2& other) {
		return { obj.x - other.x, obj.y - other.y };
	}

	inline XMINT2 operator-(const XMINT2& obj, const XMINT2& other) {
		return { obj.x - other.x, obj.y - other.y };
	}
}

template<>
struct std::formatter<::DirectX::XMFLOAT2, char>:std::formatter<const char*, char> {
	template <typename FormatContext>
	auto format(const ::DirectX::XMFLOAT2& obj, FormatContext& ctx) const {
		return format_to(ctx.out(), "[{}, {}]", obj.x, obj.y);
	}
};

template<>
struct std::formatter<::DirectX::XMINT2, char>:std::formatter<const char*, char> {
	template <typename FormatContext>
	auto format(const ::DirectX::XMINT2& obj, FormatContext& ctx) const {
		return format_to(ctx.out(), "[{}, {}]", obj.x, obj.y);
	}
};

template<>
struct std::formatter<::DirectX::XMFLOAT2, wchar_t>:std::formatter<const wchar_t*, wchar_t> {
	template <typename FormatContext>
	auto format(const ::DirectX::XMFLOAT2& obj, FormatContext& ctx) const {
		return format_to(ctx.out(), L"[{}, {}]", obj.x, obj.y);
	}
};

template<>
struct std::formatter<::DirectX::XMINT2, wchar_t>:std::formatter<const wchar_t*, wchar_t> {
	template <typename FormatContext>
	auto format(const ::DirectX::XMINT2& obj, FormatContext& ctx) const {
		return format_to(ctx.out(), L"[{}, {}]", obj.x, obj.y);
	}
};