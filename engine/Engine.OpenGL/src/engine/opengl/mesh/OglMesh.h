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
            deinit();
        }

        void init(const MeshData& mesh);

        void deinit();

        void draw();

        static const inline uint32_t VERSION = 0;
    };
}