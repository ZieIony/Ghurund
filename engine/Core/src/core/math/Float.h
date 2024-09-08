#pragma once

#include "core/DataParsing.h"
#include "core/Exceptions.h"

#include <format>

namespace Ghurund::Core {
	template<>
	inline float parse(const AString& text) {
		float val;
		auto [p, ec] = std::from_chars(&text[0], &text[text.Length], val);
		if (ec != std::errc() || p != &text[text.Length])
			throw InvalidFormatException();
		return val;
	}

	template<>
	inline double parse(const AString& text) {
		double val;
		auto [p, ec] = std::from_chars(&text[0], &text[text.Length], val);
		if (ec != std::errc() || p != &text[text.Length])
			throw InvalidFormatException();
		return val;
	}
}