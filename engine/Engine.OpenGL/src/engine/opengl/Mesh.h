#pragma once

#include "GL/glew.h"

namespace Ghurund::Engine::OpenGL {
    class Mesh {
    private:
        GLuint vertexbuffer;
        GLuint VertexArrayID;

    public:
        ~Mesh() {
            uninit();
        }

        void init() {
            glGenVertexArrays(1, &VertexArrayID);
            glBindVertexArray(VertexArrayID);

            static const GLfloat g_vertex_buffer_data[] = {
                -0.8f, -0.8f, 0.0f,
                 0.8f, -0.8f, 0.0f,
                 0.8f,  0.8f, 0.0f,
                 0.8f,  0.8f, 0.0f,
                -0.8f,  0.8f, 0.0f,
                -0.8f, -0.8f, 0.0f
            };

            glGenBuffers(1, &vertexbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
            glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
            );
        }

        void uninit() {
            glDeleteBuffers(1, &vertexbuffer);
            glDeleteVertexArrays(1, &VertexArrayID);
        }

        void draw() {
            // 1rst attribute buffer : vertices
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

            // Draw the triangle !
            glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

            glDisableVertexAttribArray(0);
        }
    };
}