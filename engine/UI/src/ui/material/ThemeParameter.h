#pragma once

#include "core/string/String.h"

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	enum class ThemeParameterType {
		COLOR, DIMENSION
	};

	struct ThemeParameter {
		AString name;
		AString key;
		ThemeParameterType type;
	};
}
