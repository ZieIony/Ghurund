#pragma once

#include "graphics/mesh/Mesh.h"
#include "resource/ResourceManager.h"

namespace Ghurund {
    class QuadMesh: public Mesh {
    protected:
        Status init(Graphics& graphics, CommandList& commandList, unsigned int detail = 0) {
            ScreenVertex quadVertices[] = {
                {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
                {{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
                {{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},

                {{1.0f, 0.0f, 0.0f},{1.0f, 0.0f}},
                {{0.0f, 1.0f, 0.0f},{0.0f, 1.0f}},
                {{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}
            };

            vertexSize = sizeof(ScreenVertex);
            vertexCount = sizeof(quadVertices) / vertexSize;
            vertices = ghnew Vertex[vertexCount];
            memcpy(vertices, quadVertices, vertexCount * vertexSize);

            indices = ghnew unsigned int[6]{
                0, 1, 2,
                3, 4, 5
            };

            indexCount = 6;

            return Mesh::init(graphics, commandList);
        }
    };
}