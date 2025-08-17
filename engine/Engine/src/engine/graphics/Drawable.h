#pragma once

#include "IMaterial.h"
#include <cstdint>
#include <DirectXMath.h>
#include "mesh/MeshData.h"

namespace Ghurund::Engine {
	struct Drawable {
		uint32_t priority;
		IMaterial* material;
		XMFLOAT4X4 transform;
		MeshData* mesh;
	};
}