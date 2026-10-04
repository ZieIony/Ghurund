#include "ghepch.h"
#include "SpriteMeshData.h"

#include "engine/graphics/mesh/MeshProcessor.h"

void Ghurund::Engine::SpriteMeshData::init() {
	VertexStream positionStream = VertexStream(List<XMFLOAT3>({
		{ 0.5f, -0.5f, 0.0f },
		{ 0.5f, 0.5f, 0.0f },
		{ -0.5f, -0.5f, 0.0f },
		{ -0.5f, 0.5f, 0.0f },
	}), VertexRole::POSITION);

	VertexStream tcStream = VertexStream(List<XMFLOAT2>({
		{ 1.0f, 1.0f },
		{ 1.0f, 0.0f },
		{ 0.0f, 1.0f },
		{ 0.0f, 0.0f },
	}), VertexRole::TEXCOORD);

	List<uint16_t> indices = {
		0, 1, 2, // first triangle
		2, 1, 3, // second triangle
	};

	auto boundingBox = MeshProcessor::computeBoundingBox(positionStream);

	MeshData::init({ positionStream, tcStream }, vertexCount = 4, indices, boundingBox);
}
