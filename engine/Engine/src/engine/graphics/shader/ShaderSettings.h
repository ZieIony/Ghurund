#pragma once

#include "core/DataParsing.h"
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

	struct VertexShaderSettings {
		CullMode cullMode = CullMode::BACK;
		bool isDepthTestEnabled = true;
		bool isDepthWriteEnabled = true;
		ComparisonFunc depthFunc = ComparisonFunc::LESS;
	};

	struct PixelShaderSettings {
		bool isTransparencyEnabled = false;
	};
}

namespace Ghurund::Core {
	using namespace Ghurund::Engine;

	template<>
	inline CullMode parse(const WString& text) {
		if (text == L"none") {
			return CullMode::NONE;
		} else if (text == L"front") {
			return CullMode::FRONT;
		} else {
			return CullMode::BACK;
		}
	}

	template<>
	inline ComparisonFunc parse(const WString& text) {
		if (text == L"never") {
			return ComparisonFunc::NEVER;
		} else if (text == L"always") {
			return ComparisonFunc::ALWAYS;
		} else if (text == L"greater") {
			return ComparisonFunc::GREATER;
		} else {
			return ComparisonFunc::LESS;
		}
	}
}
