#include "SphereMesh.h"

namespace Ghurund {
    Status SphereMesh::init(Graphics& graphics, CommandList& commandList, unsigned int detail) {
        float t = (1.0f + sqrtf(5.0f)) / 2.0f;

        Vertex triangleVertices[] = {
            {{-1.0, t, 0.0},{0,0}},
            {{1.0, t, 0.0},{0,0}},
            {{-1.0, -t, 0.0},{0,0}},
            {{1.0, -t, 0.0},{0,0}},
            {{0.0, -1.0, t},{0,0}},
            {{0.0, 1.0, t},{0,0}},
            {{0.0, -1.0, -t},{0,0}},
            {{0.0, 1.0, -t},{0,0}},
            {{t, 0.0, -1.0},{0,0}},
            {{t, 0.0, 1.0},{0,0}},
            {{-t, 0.0, -1.0},{0,0}},
            {{-t, 0.0, 1.0},{0,0}}
        };

        vertexSize = sizeof(Vertex);
        vertexCount = sizeof(triangleVertices) / vertexSize;
        vertices = ghnew Vertex[vertexCount];
        memcpy(vertices, triangleVertices, vertexCount * vertexSize);

        indices = ghnew unsigned int[60]{
            0, 11, 5,
            0, 5, 1,
            0, 1, 7,
            0, 7, 10,
            0, 10, 11,
            1, 5, 9,
            5, 11, 4,
            11, 10, 2,
            10, 7, 6,
            7, 1, 8,
            3, 9, 4,
            3, 4, 2,
            3, 2, 6,
            3, 6, 8,
            3, 8, 9,
            4, 9, 5,
            2, 4, 11,
            6, 2, 10,
            8, 6, 7,
            9, 8, 1
        };
        indexCount = 60;

        spherify();

        for (size_t i = 0; i < vertexCount; i++) {
            XMFLOAT3 v = ((Vertex*)vertices)[i].position;
            ((Vertex*)vertices)[i].texCoord.x = atan2f(v.x, v.z) / (2 * XM_PI) + 0.5f;
            ((Vertex*)vertices)[i].texCoord.y = v.y * 0.5f + 0.5f;
        }

        for (size_t i = 0; i < detail; i++) {
            subdivide();
            removeDuplicates();
            spherify();
        }

        generateNormals();

        return Mesh::init(graphics, commandList);
    }
}