#pragma once

#include "core/DataParsing.h"

namespace Ghurund::Engine {
    enum class TextureFilter {
        POINT, LINEAR, ANISOTROPIC
    };
}

namespace Ghurund::Core {
	using namespace Ghurund::Engine;

	template<>
	inline TextureFilter parse(const WString& text) {
		if (text == L"point") {
			return TextureFilter::POINT;
		} else if (text == L"anisotropic") {
			return TextureFilter::ANISOTROPIC;
		} else {
			return TextureFilter::LINEAR;
		}
	}
}
