#include "engine/opengl/Shader.h"

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

namespace Ghurund::Engine::OpenGL {
    class Renderer {
    public:
        ~Renderer() {
            uninit();
        }

        void init() {
            if (!glfwInit())
                throw CallFailedException("Failed to initialize GLFW\n");

            glfwWindowHint(GLFW_SAMPLES, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            if (glewInit() != GLEW_OK)
                throw CallFailedException("Failed to initialize GLEW\n");
        }

        void uninit() {
            glfwTerminate();
        }

        void clear() {
            glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        }
    };

    class OpenGLWindow {
    private:
        GLFWwindow* window = nullptr;

    protected:
        virtual void onDraw() {}

    public:
        void init() {
            window = glfwCreateWindow(1024, 768, "Tutorial 01", nullptr, nullptr);
            if (window == nullptr)
                throw CallFailedException("Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\n");
        }

        void draw() {
            glfwMakeContextCurrent(window);
            glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

            do {

                // Clear the screen
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                onDraw();

                // Swap buffers
                glfwSwapBuffers(window);
                glfwPollEvents();

            } // Check if the ESC key was pressed or the window was closed
            while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
                glfwWindowShouldClose(window) == 0);
        }
    };

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

using namespace Ghurund::Engine::OpenGL;

class SampleWindow:public OpenGLWindow {
private:
    Shader shader;
    Mesh mesh;

public:
    void init() {
        shader.init(FilePath(L"resources/shaders/OpenGL/rect.vert"), FilePath(L"resources/shaders/OpenGL/rect.frag"));
        mesh.init();
    }

    virtual void onDraw() override {
        shader.set();

        GLuint resolutionId = glGetUniformLocation(shader.Id, "resolution");
        glUniform2f(resolutionId, 1024, 768);

        mesh.draw();
    }
};

int main() {
    Renderer renderer;
    renderer.init();
    SampleWindow window;
    window.init();
    window.draw();
    return 0;
}