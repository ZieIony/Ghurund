#pragma once

#include "core/object/IntrusivePointer.h"
#include "engine/graphics/material/Material.h"
#include "mesh/Mesh.h"

#include <DirectXMath.h>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;
	using namespace ::DirectX;

	struct DrawPacket {
		IntrusivePointer<Mesh> mesh;
		IntrusivePointer<Material> material;
		XMFLOAT3 position;
	};
}