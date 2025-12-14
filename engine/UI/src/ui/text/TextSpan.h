#pragma once

#include "core/Color.h"
#include "core/string/String.h"
#include "ui/font/Font.h"

namespace Ghurund::UI {
	struct TextSpan{
		size_t start, finish;
		const Font* font;
		Color color;
	};
}