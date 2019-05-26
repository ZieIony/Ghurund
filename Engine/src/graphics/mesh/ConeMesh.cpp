#include "ConeMesh.h"

namespace Ghurund {
    Status ConeMesh::init(Graphics& graphics, CommandList& commandList, unsigned int detail) {
        detail = max<unsigned int>(detail, 3);

        List<Vertex> triangleVertices;
        triangleVertices.add({{0.0f,  0.0f, 0.0f},{0,0}});
        triangleVertices.add({{0.0f,  1.0f, 0.0f},{0,1.0f}});

        List<vindex_t> triangleIndices;
        List<vindex_t> triangleIndices2;
        for (vindex_t i = 0; i < detail; i++) {
            float x = cosf(2 * XM_PI * i / detail);
            float z = sinf(2 * XM_PI * i / detail);
            float t = i / detail + 0.5f;
            triangleVertices.add({{x,0.0f,z}, {t,0}});
            triangleIndices.add(i + 2);
            triangleIndices.add((i + 1) % detail+2);
            triangleIndices.add(0);
            triangleIndices2.add(i + 2);
            triangleIndices2.add(1);
            triangleIndices2.add((i + 1) % detail + 2);
        }

        vertexSize = sizeof(Vertex);
        vertexCount = (vindex_t)triangleVertices.Size;
        vertices = ghnew Vertex[vertexCount];
        memcpy(vertices, triangleVertices.begin(), vertexCount * vertexSize);

        indexCount = (vindex_t)(triangleIndices.Size + triangleIndices2.Size);
        indices = ghnew vindex_t[indexCount];
        memcpy(indices, triangleIndices.begin(), triangleIndices.Size * sizeof(vindex_t));
        memcpy(indices + triangleIndices.Size, triangleIndices2.begin(), triangleIndices2.Size * sizeof(vindex_t));

        generateNormals();

        return Mesh::init(graphics, commandList);
    }
}