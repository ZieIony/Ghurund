#pragma once

#include "graphics/Mesh.h"
#include "resource/ResourceManager.h"

namespace Ghurund {
    class ConeMesh: public Mesh {
    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size) {
            Vertex triangleVertices[] = {
                { { -0.5f,  0.5f, -0.5f },{ 0,0,-1 },{ 0,0 } }
            };

            vertexSize = sizeof(Vertex);
            vertexCount = sizeof(triangleVertices) / vertexSize;
            vertices = ghnew BYTE[vertexCount*vertexSize];
            memcpy(vertices, triangleVertices, vertexCount*vertexSize);

            indices = ghnew unsigned int[36]{
                20
            };
            indexCount = 36;

            return Mesh::init(resourceManager.getGraphics(), resourceManager.getCommandList());
        }

        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size, unsigned int flags = 0)const {
            return Status::NOT_IMPLEMENTED;
        }

    };
}