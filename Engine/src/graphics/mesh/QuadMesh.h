#pragma once

#include "graphics/mesh/Mesh.h"
#include "resource/ResourceManager.h"

namespace Ghurund {
    class QuadMesh: public Mesh {
    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, ResourceContext &context, const void *data, unsigned long size) {
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
            vertices = ghnew BYTE[vertexCount*vertexSize];
            memcpy(vertices, quadVertices, vertexCount*vertexSize);

            indices = ghnew unsigned int[6]{
                0, 1, 2,
                3, 4, 5
            };

            indexCount = 6;

            return Mesh::init(context.Graphics, context.CommandList);
        }
    };
}