#include "ghe2dpch.h"
#include "TileMapMeshData.h"

namespace Ghurund::Engine::_2D {
	void TileMapMeshData::init(IntSize tileMapSize, Array<TileInfo>& tiles) {
		List<XMFLOAT2> vertices;
		List<XMFLOAT2> texCoords;
		List<uint32_t> indices;

		float left = tileMapSize.Width / -2.0f;
		float top = tileMapSize.Height / 2.0f;
		uint32_t i = 0;
		uint32_t tileIndex = 0;
		for (auto& tile : tiles) {
			uint32_t x = tileIndex % tileMapSize.Width;
			uint32_t y = tileIndex / tileMapSize.Width;
			vertices.addAll({
				{ left + x, top - y },
				{ left + x, top - y - 1.0f },
				{ left + x + 1.0f, top - y },
				{ left + x + 1.0f, top - y - 1.0f }
				});
			texCoords.addAll({
				tile.texCoordTopLeft,
				{ tile.texCoordTopLeft.x, tile.texCoordBottomRight.y },
				{ tile.texCoordBottomRight.x, tile.texCoordTopLeft.y },
				tile.texCoordBottomRight
				});
			indices.addAll({ i, i + 1, i + 2, i + 2, i + 1, i + 3 });
			tileIndex++;
			i += 4;
		}
		VertexStream posStream = VertexStream(vertices, VertexRole::POSITION);
		VertexStream texCoordStream = VertexStream(texCoords, VertexRole::TEXCOORD);

		MeshData::init({ posStream, texCoordStream }, (uint32_t)vertices.Size, indices);
	}
}
