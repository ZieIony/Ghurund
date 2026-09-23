#pragma once

#include "MeshData.h"

namespace Ghurund::Engine {
	class QuadMeshData: public MeshData {
	public:
		void init() {
			VertexStream posStream = VertexStream(List<XMFLOAT2>({
				{-1.0f, -1.0f},
				{-1.0f, 1.0f},
				{1.0f, -1.0f},
				{1.0f, 1.0f},
				}), VertexRole::POSITION);

			VertexStream texCoordStream = VertexStream(List<XMFLOAT2>({
				{0,0},
				{0,1},
				{1,0},
				{1,1},
			}), VertexRole::TEXCOORD);

			List<uint16_t> indices = {
				0, 1, 2, // first triangle
				2, 1, 3, // second triangle
			};

			MeshData::init({ posStream, texCoordStream }, vertexCount = 4, indices);
		}
	};
}