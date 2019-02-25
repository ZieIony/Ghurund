#pragma once

#include "Mesh.h"
#include "resource/ResourceManager.h"

namespace Ghurund {
    class CubeMesh: public Mesh {
    public:
        Status init(Graphics &graphics, CommandList &commandList, unsigned int detail = 0) {
            Vertex triangleVertices[] = {
                {{-1.0f,  1.0f, -1.0f}, {0,0,-1}, {0,0}},
                {{ 1.0f, -1.0f, -1.0f}, {0,0,-1}, {1,1}},
                {{-1.0f, -1.0f, -1.0f}, {0,0,-1}, {0,1}},
                {{ 1.0f,  1.0f, -1.0f}, {0,0,-1}, {1,0}},

                // right side face
                {{1.0f, -1.0f, -1.0f}, {1,0,0}, {0,0}},
                {{1.0f,  1.0f,  1.0f}, {1,0,0}, {1,1}},
                {{1.0f, -1.0f,  1.0f}, {1,0,0}, {0,1}},
                {{1.0f,  1.0f, -1.0f}, {1,0,0}, {1,0}},

                // left side face
                {{-1.0f,  1.0f,  1.0f}, {-1,0,0}, {0,0}},
                {{-1.0f, -1.0f, -1.0f}, {-1,0,0}, {1,1}},
                {{-1.0f, -1.0f,  1.0f}, {-1,0,0}, {0,1}},
                {{-1.0f,  1.0f, -1.0f}, {-1,0,0}, {1,0}},

                // back face
                {{1.0f,   1.0f,  1.0f}, {0,0,1}, {0,0}},
                {{-1.0f, -1.0f,  1.0f}, {0,0,1}, {1,1}},
                {{1.0f,  -1.0f,  1.0f}, {0,0,1}, {0,1}},
                {{-1.0f,  1.0f,  1.0f}, {0,0,1}, {1,0}},

                // top face
                {{-1.0f, 1.0f, -1.0f}, {0,1,0}, {0,0}},
                {{1.0f,  1.0f,  1.0f}, {0,1,0}, {1,1}},
                {{1.0f,  1.0f, -1.0f}, {0,1,0}, {0,1}},
                {{-1.0f, 1.0f,  1.0f}, {0,1,0}, {1,0}},

                // bottom face
                {{1.0f,  -1.0f,  1.0f}, {0,-1,0}, {0,0}},
                {{-1.0f, -1.0f, -1.0f}, {0,-1,0}, {1,1}},
                {{1.0f,  -1.0f, -1.0f}, {0,-1,0}, {0,1}},
                {{-1.0f, -1.0f,  1.0f}, {0,-1,0}, {1,0}},
            };

            vertexSize = sizeof(Vertex);
            vertexCount = sizeof(triangleVertices)/vertexSize;
            vertices = ghnew Vertex[vertexCount];
            memcpy(vertices, triangleVertices, vertexCount*vertexSize);

            indices = ghnew unsigned int[36]{
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

            return Mesh::init(graphics, commandList);
        }
    };
}