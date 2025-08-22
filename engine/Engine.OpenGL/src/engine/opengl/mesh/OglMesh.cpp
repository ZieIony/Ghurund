#include "gheoglpch.h"
#include "OglMesh.h"

namespace Ghurund::Engine::OpenGL {
    void OglMesh::init(NotNull<MeshData> mesh) {
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        vertexCount = mesh->VertexCount;
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, mesh->VertexStreams[0].data.Size, mesh->VertexStreams[0].data.Data, GL_STATIC_DRAW);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );
    }
    
    void OglMesh::uninit() {
        glDeleteBuffers(1, &vertexbuffer);
        glDeleteVertexArrays(1, &VertexArrayID);
    }
    
    void OglMesh::draw() {
        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, vertexCount); // 3 indices starting at 0 -> 1 triangle

        glDisableVertexAttribArray(0);
    }
}