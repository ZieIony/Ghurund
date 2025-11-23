#pragma once

#include "MeshData.h"

namespace Ghurund::Engine {
    class PlaneMeshData: public MeshData {
    public:
        void init(unsigned int detail = 0) {
            VertexStream posStream = VertexStream(List<XMFLOAT3>({
                {-1.0f, 0.0f, -1.0f},
                {1.0f,  0.0f,  1.0f},
                {1.0f,  0.0f, -1.0f},
                {-1.0f, 0.0f,  1.0f},
            }), VertexRole::POSITION);
            VertexStream normalStream = VertexStream(List<XMFLOAT3>({
                {0,1,0},
                {0,1,0},
                {0,1,0},
                {0,1,0},
            }), VertexRole::NORMAL);
            VertexStream texCoordStream = VertexStream(List<XMFLOAT2>({
                {0,0},
                {1,1},
                {0,1},
                {1,0},
            }), VertexRole::TEXCOORD);

            vertexCount = 4;

            List<uint16_t> indices = {
                0, 1, 2, // first triangle
                0, 3, 1, // second triangle
            };

            //for (size_t i = 0; i < detail; i++)
              //  subdivide();

			MeshData::init({ posStream, normalStream, texCoordStream }, vertexCount, indices);
        }
    };
}