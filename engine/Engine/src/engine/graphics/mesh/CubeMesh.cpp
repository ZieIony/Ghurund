#include "ghepch.h"
#include "CubeMesh.h"
#include "core/collection/Array.h"

namespace Ghurund::Engine {
    void CubeMesh::init(unsigned int detail) {
		auto positions = Array<XMFLOAT3>({
			{-1.0f,  1.0f, -1.0f},
			{1.0f, -1.0f, -1.0f},
			{-1.0f, -1.0f, -1.0f},
			{1.0f,  1.0f, -1.0f},

			// right side face
			{1.0f, -1.0f, -1.0f},
			{1.0f,  1.0f,  1.0f},
			{1.0f, -1.0f,  1.0f},
			{1.0f,  1.0f, -1.0f},

			// left side face
			{-1.0f,  1.0f,  1.0f},
			{-1.0f, -1.0f, -1.0f},
			{-1.0f, -1.0f,  1.0f},
			{-1.0f,  1.0f, -1.0f},

			// back face
			{1.0f,   1.0f,  1.0f},
			{-1.0f, -1.0f,  1.0f},
			{1.0f,  -1.0f,  1.0f},
			{-1.0f,  1.0f,  1.0f},

			// top face
			{-1.0f, 1.0f, -1.0f},
			{1.0f,  1.0f,  1.0f},
			{1.0f,  1.0f, -1.0f},
			{-1.0f, 1.0f,  1.0f},

			// bottom face
			{1.0f,  -1.0f,  1.0f},
			{-1.0f, -1.0f, -1.0f},
			{1.0f,  -1.0f, -1.0f},
			{-1.0f, -1.0f,  1.0f}
		});
		VertexStream positionStream = VertexStream(positions, VertexRole::POSITION);
		VertexStream normalStream = VertexStream(Array<XMFLOAT3>({
			{0,0,-1},{0,0,-1},{0,0,-1},{0,0,-1},

			// right side face
			{1,0,0},{1,0,0},{1,0,0},{1,0,0},

			// left side face
			{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},

			// back face
			{0,0,1},{0,0,1},{0,0,1},{0,0,1},

			// top face
			{0,1,0},{0,1,0},{0,1,0},{0,1,0},

			// bottom face
			{0,-1,0},{0,-1,0},{0,-1,0},{0,-1,0}
		}), VertexRole::NORMAL);
		VertexStream texCoordStream = VertexStream(Array<XMFLOAT2>({
			{0,0},
			{1,1},
			{0,1},
			{1,0},

			// right side face
			{0,0},
			{1,1},
			{0,1},
			{1,0},

			// left side face
			{0,0},
			{1,1},
			{0,1},
			{1,0},

			// back face
			{0,0},
			{1,1},
			{0,1},
			{1,0},

			// top face
			{0,0},
			{1,1},
			{0,1},
			{1,0},

			// bottom face
			{0,0},
			{1,1},
			{0,1},
			{1,0},
		}), VertexRole::TEXCOORD);

		Ghurund::Core::Array<uint16_t> indices = {
			// front face
			0, 1, 2, // first triangle
			0, 3, 1, // second triangle

			// left face
			4, 5, 6, // first triangle
			4, 7, 5, // second triangle

			// right face
			8, 9, 10, // first triangle
			8, 11, 9, // second triangle

			// back face
			12, 13, 14, // first triangle
			12, 15, 13, // second triangle

			// top face
			16, 17, 18, // first triangle
			16, 19, 17, // second triangle

			// bottom face
			20, 21, 22, // first triangle
			20, 23, 21, // second triangle
		};

        MeshData::init({positionStream, normalStream, texCoordStream}, (uint32_t)positions.Size, indices);
    }
}