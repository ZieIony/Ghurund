#pragma once

#include "IMaterial.h"
#include <cstdint>
#include <DirectXMath.h>

namespace Ghurund::Engine {
	using namespace ::DirectX;

	struct Drawable {
		uint32_t priority;
		IMaterial* material;
		XMFLOAT4X4 transform;
		Mesh* mesh;
	};
}