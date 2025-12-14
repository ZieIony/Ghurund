#pragma once

#include "ui/font/GlyphMetrics.h"

#include <DirectXMath.h>

namespace Ghurund::UI {
	struct CharacterInfo {
		wchar_t c;
		XMFLOAT2 pos;
		GlyphMetrics glyph;
	};
}