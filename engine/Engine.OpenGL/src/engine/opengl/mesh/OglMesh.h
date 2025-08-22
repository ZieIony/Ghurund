#pragma once

#include "GL/glew.h"
#include <engine/graphics/mesh/MeshData.h>

namespace Ghurund::Engine::OpenGL {
    class OglMesh:public Resource {
    private:
        GLuint vertexbuffer;
        GLuint VertexArrayID;
        uint32_t vertexCount;

    public:
        ~OglMesh() {
            uninit();
        }

        void init(NotNull<MeshData> mesh);

        void uninit();

        void draw();
    };
}