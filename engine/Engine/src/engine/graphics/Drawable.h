#pragma once

#include "mesh/MeshData.h"
#include "material/IMaterial.h"

#include <DirectXMath.h>
#include <cstdint>

namespace Ghurund::Engine {
	struct Drawable {
		uint32_t priority;
		IMaterial* material;
		XMFLOAT4X4 transform;
		MeshData* mesh;
	};
}