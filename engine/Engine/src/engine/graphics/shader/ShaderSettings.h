#pragma once

#include "core/string/String.h"
#include "engine/graphics/texture/TextureFilter.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	struct SamplerInfo {
		AString name;
		TextureFilter filter;
	};

	enum class CullMode {
		NONE, FRONT, BACK
	};

	enum class ComparisonFunc {
		NEVER, ALWAYS, LESS, GREATER
	};

	struct ShaderSettings {
		bool isTransparencyEnabled = false;
		CullMode cullMode = CullMode::BACK;
		bool isDepthTestEnabled = true;
		bool isDepthWriteEnabled = true;
		ComparisonFunc depthFunc = ComparisonFunc::LESS;
	};
}
