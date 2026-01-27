#pragma once

#include "core/collection/List.h"
#include "core/string/String.h"
#include "engine/graphics/texture/TextureFilter.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	enum class CullMode {
		NONE, FRONT, BACK
	};

	struct SamplerInfo {
		AString name;
		TextureFilter filter;
	};

	struct ShaderSettings {
		bool isTransparencyEnabled = false;
		CullMode cullMode = CullMode::BACK;
		bool isDepthTestEnabled = true;
	};
}
