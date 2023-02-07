#pragma once

#include "Mesh.h"
#include "core/resource/ResourceManager.h"

namespace Ghurund {
    class QuadMesh: public Mesh {
    public:
        Status init(Graphics& graphics, CommandList& commandList, unsigned int detail = 0) {
            ScreenVertex quadVertices[] = {
                {{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
                {{-1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
                {{1.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},

                {{1.0f, -1.0f, 0.0f},{1.0f, 0.0f}},
                {{-1.0f, 1.0f, 0.0f},{0.0f, 1.0f}},
                {{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}
            };

            vertexSize = sizeof(ScreenVertex);
            vertexCount = sizeof(quadVertices) / vertexSize;
            vertices = ghnew ScreenVertex[vertexCount];
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