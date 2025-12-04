#pragma once

#include <d3d12.h>

namespace Ghurund::Engine::DirectX {

	struct ShaderSettings {
		bool isTransparencyEnabled;
		D3D12_CULL_MODE cullMode;
		bool isDepthTestEnabled;
	};
}