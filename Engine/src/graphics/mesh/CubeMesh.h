#pragma once

#include "Mesh.h"
#include "resource/ResourceManager.h"

namespace Ghurund {
    class CubeMesh: public Mesh {
    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size) {
            Vertex triangleVertices[] = {
                {{-0.5f,  0.5f, -0.5f}, {0,0,-1}, {0,0}},
                {{ 0.5f, -0.5f, -0.5f}, {0,0,-1}, {1,1}},
                {{-0.5f, -0.5f, -0.5f}, {0,0,-1}, {0,1}},
                {{ 0.5f,  0.5f, -0.5f}, {0,0,-1}, {1,0}},

                // right side face
                {{0.5f, -0.5f, -0.5f}, {1,0,0}, {0,0}},
                {{0.5f,  0.5f,  0.5f}, {1,0,0}, {1,1}},
                {{0.5f, -0.5f,  0.5f}, {1,0,0}, {0,1}},
                {{0.5f,  0.5f, -0.5f}, {1,0,0}, {1,0}},

                // left side face
                {{-0.5f,  0.5f,  0.5f}, {-1,0,0}, {0,0}},
                {{-0.5f, -0.5f, -0.5f}, {-1,0,0}, {1,1}},
                {{-0.5f, -0.5f,  0.5f}, {-1,0,0}, {0,1}},
                {{-0.5f,  0.5f, -0.5f}, {-1,0,0}, {1,0}},

                // back face
                {{0.5f,   0.5f,  0.5f}, {0,0,1}, {0,0}},
                {{-0.5f, -0.5f,  0.5f}, {0,0,1}, {1,1}},
                {{0.5f,  -0.5f,  0.5f}, {0,0,1}, {0,1}},
                {{-0.5f,  0.5f,  0.5f}, {0,0,1}, {1,0}},

                // top face
                {{-0.5f, 0.5f, -0.5f}, {0,1,0}, {0,0}},
                {{0.5f,  0.5f,  0.5f}, {0,1,0}, {1,1}},
                {{0.5f,  0.5f, -0.5f}, {0,1,0}, {0,1}},
                {{-0.5f, 0.5f,  0.5f}, {0,1,0}, {1,0}},

                // bottom face
                {{0.5f,  -0.5f,  0.5f}, {0,-1,0}, {0,0}},
                {{-0.5f, -0.5f, -0.5f}, {0,-1,0}, {1,1}},
                {{0.5f,  -0.5f, -0.5f}, {0,-1,0}, {0,1}},
                {{-0.5f, -0.5f,  0.5f}, {0,-1,0}, {1,0}},
            };

            vertexSize = sizeof(Vertex);
            vertexCount = sizeof(triangleVertices)/vertexSize;
            vertices = ghnew BYTE[vertexCount*vertexSize];
            memcpy(vertices, triangleVertices, vertexCount*vertexSize);

            indices = ghnew unsigned int[36] {
                // ffront face
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
            indexCount = 36;

            return Mesh::init(resourceManager.getGraphics(), resourceManager.getCommandList());
        }

        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size, unsigned int flags = 0)const {
            return Status::NOT_IMPLEMENTED;
        }

    };
}