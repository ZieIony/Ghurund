#pragma once

#include "graphics/Mesh.h"
#include "resource/ResourceManager.h"

using namespace DirectX;
using namespace Microsoft::WRL;

namespace Ghurund {
    class TriangleMesh:public Mesh {
    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned int flags = 0) {
            Vertex triangleVertices[] = {
                {{0.0f, 0.25f, 0.0f,1},{0.0f,0.0f}, { 1.0f, 0.0f, 0.0f, 1.0f }},
                {{0.25f, -0.25f, 0.0f,1},{0.0f,1.0f},{0.0f, 1.0f, 0.0f, 1.0f}},
                {{-0.25f, -0.25f, 0.0f,1},{1.0f,0.0f},{0.0f, 0.0f, 1.0f, 1.0f}}
            };

            vertexSize = sizeof(Vertex);
            vertexCount = sizeof(triangleVertices)/vertexSize;
            vertices = ghnew BYTE[vertexCount*vertexSize];
            memcpy(vertices, triangleVertices, vertexCount*vertexSize);

            indices = ghnew unsigned int[3];
            indices[0] = 0;
            indices[1] = 1;
            indices[2] = 2;
            indexCount = 3;

            return Mesh::init(resourceManager.getGraphics(), resourceManager.getCommandList());
        }

        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size, unsigned int flags = 0)const {
            return Status::NOT_IMPLEMENTED;
        }
    };
}