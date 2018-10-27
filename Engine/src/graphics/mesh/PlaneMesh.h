#pragma once

#include "Mesh.h"
#include "resource/ResourceManager.h"

namespace Ghurund {
    class PlaneMesh: public Mesh {
    public:
        Status init(Graphics &graphics, CommandList &commandList) {
            Vertex triangleVertices[] = {
                {{-1.0f, 0.0f, -1.0f}, {0,1,0}, {0,0}},
                {{1.0f,  0.0f,  1.0f}, {0,1,0}, {1,1}},
                {{1.0f,  0.0f, -1.0f}, {0,1,0}, {0,1}},
                {{-1.0f, 0.0f,  1.0f}, {0,1,0}, {1,0}},
            };

            vertexSize = sizeof(Vertex);
            vertexCount = sizeof(triangleVertices)/vertexSize;
            vertices = ghnew Vertex[vertexCount];
            memcpy(vertices, triangleVertices, vertexCount*vertexSize);

            indices = ghnew unsigned int[6]{
                0, 1, 2, // first triangle
                0, 3, 1, // second triangle
            };
            indexCount = 6;

            return Mesh::init(graphics, commandList);
        }
    };
}