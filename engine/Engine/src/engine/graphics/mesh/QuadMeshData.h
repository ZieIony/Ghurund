#pragma once

#include "MeshData.h"

namespace Ghurund::Engine {
	class QuadMeshData: public MeshData {
	public:
		void init() {
			VertexStream posStream = VertexStream(List<XMFLOAT2>({
				{0.0f, 0.0f},
				{0.0f, 1.0f},
				{1.0f, 0.0f},
				{1.0f, 1.0f},
			}), VertexRole::POSITION);

			List<uint16_t> indices = {
				0, 1, 2, // first triangle
				2, 1, 3, // second triangle
			};

			MeshData::init({ posStream }, vertexCount = 4, indices);
		}
	};
}