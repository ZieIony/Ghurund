#pragma once

#include "engine/graphics/mesh/MeshData.h"

#include <GL/glew.h>

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

        void init(const MeshData& mesh);

        void uninit();

        void draw();
    };
}