#pragma once

#include "core/collection/List.h"
#include "core/string/String.h"
#include "engine/graphics/texture/TextureFilter.h"

#include <d3d12.h>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	struct SamplerInfo {
		AString name;
		TextureFilter filter;
	};

	struct ShaderSettings {
		bool isTransparencyEnabled = false;
		D3D12_CULL_MODE cullMode = D3D12_CULL_MODE::D3D12_CULL_MODE_BACK;
		bool isDepthTestEnabled = true;
		bool isDepthWriteEnabled = true;
		D3D12_COMPARISON_FUNC depthFunc = D3D12_COMPARISON_FUNC::D3D12_COMPARISON_FUNC_LESS;
	};
}
