#pragma once

#include <core/math/Size.h>
#include "engine/graphics/mesh/MeshData.h"

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;

	struct TileInfo {
		XMFLOAT2 texCoordTopLeft, texCoordBottomRight;
	};

	class TileMapMeshData: public MeshData {
	public:
		void init(IntSize tileMapSize, Array<TileInfo>& tiles);
	};
}
