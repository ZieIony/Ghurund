#pragma once

#include "core/Color.h"
#include "ui/font/TextStyle.h"

namespace Ghurund::UI {
	struct TextSpan{
		size_t start, finish;
		const TextStyle* textStyle;
		Color color;
	};
}