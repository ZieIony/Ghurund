#pragma once

#include "core/object/IntrusivePointer.h"
#include "core/resource/Resource.h"
#include "engine/graphics/material/Material.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	struct DrawPacket {
		IntrusivePointer<Resource> mesh;
		IntrusivePointer<Material> material;
		XMFLOAT3 position;
	};
}