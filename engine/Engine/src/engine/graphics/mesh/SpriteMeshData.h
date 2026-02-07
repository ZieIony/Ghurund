#pragma once

#include "MeshData.h"

namespace Ghurund::Engine {
	class SpriteMeshData: public MeshData {
	public:
		void init() {
			VertexStream posStream = VertexStream(List<XMFLOAT3>({
				{0.5f, -0.5f, 0.0f},
				{0.5f, 0.5f, 0.0f},
				{-0.5f, -0.5f, 0.0f},
				{-0.5f, 0.5f, 0.0f},
				}), VertexRole::POSITION);

			VertexStream tcStream = VertexStream(List<XMFLOAT2>({
				{1.0f, 1.0f},
				{1.0f, 0.0f},
				{0.0f, 1.0f},
				{0.0f, 0.0f},
				}), VertexRole::TEXCOORD);

			List<uint16_t> indices = {
				0, 1, 2, // first triangle
				2, 1, 3, // second triangle
			};

			MeshData::init({ posStream, tcStream }, vertexCount = 4, indices);
		}
	};
}