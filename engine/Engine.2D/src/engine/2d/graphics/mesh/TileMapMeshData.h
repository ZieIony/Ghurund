#pragma once

#include "engine/graphics/mesh/MeshData.h"

namespace Ghurund::Engine::_2D {
	struct TileInfo {
		XMFLOAT2 texCoordTopLeft, texCoordBottomRight;
	};

	class TileMapMeshData: public MeshData {
	public:
		void init(IntSize tileMapSize, Array<TileInfo>& tiles);
	};
}
