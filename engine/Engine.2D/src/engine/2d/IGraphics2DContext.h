#pragma once

#include "engine/graphics/material/Material.h"
#include "engine/graphics/mesh/Mesh.h"
#include "graphics/mesh/TileMapMeshData.h"

namespace Ghurund::Engine::_2D {
	class IGraphics2DContext {
	public:
		virtual Mesh* makeSpriteMesh() = 0;

		virtual Material* makeSpriteMaterial() = 0;

		virtual Mesh* makeTileMapMesh(IntSize tileMapSize, Array<TileInfo>& tiles) = 0;

		virtual Material* makeTileMapMaterial() = 0;

		virtual Material* makeBoxVisualizationMaterial() = 0;

		virtual Material* makeCapsuleVisualizationMaterial() = 0;

		virtual Material* makeSegmentVisualizationMaterial() = 0;
	};
}
