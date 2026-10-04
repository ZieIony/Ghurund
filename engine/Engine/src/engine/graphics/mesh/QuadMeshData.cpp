#include "ghepch.h"
#include "QuadMeshData.h"

#include "MeshProcessor.h"

namespace Ghurund::Engine {
	void QuadMeshData::init() {
		VertexStream positionStream = VertexStream(List<XMFLOAT2>({
			{ -1.0f, -1.0f },
			{ -1.0f, 1.0f },
			{ 1.0f, -1.0f },
			{ 1.0f, 1.0f },
		}), VertexRole::POSITION);

		VertexStream texCoordStream = VertexStream(List<XMFLOAT2>({
			{ 0,0 },
			{ 0,1 },
			{ 1,0 },
			{ 1,1 },
		}), VertexRole::TEXCOORD);

		List<uint16_t> indices = {
			0, 1, 2, // first triangle
			2, 1, 3, // second triangle
		};

		auto boundingBox = MeshProcessor::computeBoundingBox(positionStream);

		__super::init({ positionStream, texCoordStream }, vertexCount = 4, indices, boundingBox);
	}
}
