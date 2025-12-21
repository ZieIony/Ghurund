#pragma once

#include "mesh/MeshData.h"
#include "material/Material.h"

#include <DirectXMath.h>
#include <cstdint>

namespace Ghurund::Engine {
	struct Drawable {
		uint32_t priority;
		Material* material;
		XMFLOAT4X4 transform;
		MeshData* mesh;
	};
}