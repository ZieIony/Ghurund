#pragma once

#include "Int.h"

#include "core/string/String.h"
#include "core/DataParsing.h"

#include <regex>
#include <format>
#include <DirectXMath.h>

namespace Ghurund::Core {
	template<typename T>
	class BaseSize {
	private:
		T width, height;

	public:
		BaseSize():width(0), height(0) {}

		BaseSize(T width, T height):width(std::max((T)0, width)), height(std::max((T)0, height)) {}

		inline T getWidth() const {
			return width;
		}

		inline void setWidth(const T width) {
			this->width = std::max((T)0, width);
		}

		__declspec(property(get = getWidth, put = setWidth)) const T Width;

		inline T getHeight() const {
			return height;
		}

		inline void setHeight(const T height) {
			this->height = std::max((T)0, height);
		}

		__declspec(property(get = getHeight, put = setHeight)) const T Height;

		inline bool operator==(const BaseSize<T>& other) const {
			return width == other.width && height == other.height;
		}

		inline auto operator<=>(const BaseSize<T>& other) const = default;

		inline BaseSize<T> operator+(const BaseSize<T>& other) const {
			return { width + other.width, height + other.height };
		}

		inline BaseSize<T> operator-(const BaseSize<T>& other) const {
			return { width - other.width, height - other.height };
		}

		static BaseSize<T> parse(const AString& text) {
			std::regex regex(" *(.*) *, *(.*) *");
			std::smatch m;
			std::string s = text.Data;
			if (std::regex_match(s, m, regex)) {
				T width = Ghurund::Core::parse<T>(m[1].str().c_str());
				T height = Ghurund::Core::parse<T>(m[2].str().c_str());
				return { width, height };
			} else {
				throw std::invalid_argument("invalid alignment string");
			}
		}

		inline String toString() const {
			return String(std::format(_T("{}, {}"), width, height).c_str());
		}
	};

	typedef BaseSize<uint32_t> IntSize;
	typedef BaseSize<float> FloatSize;

	template<>
	inline String toString(const ::DirectX::XMINT2& value) {
		return String(std::format(_T("{}, {}"), value.x, value.y).c_str());
	}

	template<>
	inline ::DirectX::XMINT2 parse(const AString& text) {
		std::regex regex(" *(d+) *, *(d+) *");
		std::smatch m;
		std::string s = text.Data;
		if (std::regex_match(s, m, regex)) {
			int32_t width = Ghurund::Core::parse<int32_t>(m[1].str().c_str());
			int32_t height = Ghurund::Core::parse<int32_t>(m[2].str().c_str());
			return { width, height };
		} else {
			throw std::invalid_argument("invalid alignment string");
		}
	}
}

template <typename T>
struct std::formatter<Ghurund::Core::BaseSize<T>, char>:std::formatter<const char*, char> {
	template <typename FormatContext>
	auto format(const Ghurund::Core::BaseSize<T>& obj, FormatContext& ctx) const {
		return format_to(ctx.out(), "{}", obj.toString());
	}
};

template <typename T>
struct std::formatter<Ghurund::Core::BaseSize<T>, wchar_t>:std::formatter<const wchar_t*, wchar_t> {
	template <typename FormatContext>
	auto format(const Ghurund::Core::BaseSize<T>& obj, FormatContext& ctx) const {
		return format_to(ctx.out(), L"{}", obj.toString());
	}
};