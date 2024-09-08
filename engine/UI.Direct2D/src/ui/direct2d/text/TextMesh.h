#pragma once

#include "core/directx/mesh/Mesh.h"
#include <ui/font/Font.h>

namespace Ghurund::UI {
	class TextMesh :public Ghurund::Mesh {
    public:
        Status init(Graphics& graphics, CommandList& commandList, Font& font, const String& text) {
            Vertex quadVertices[] = {
                {{-1.0f, 0.0f, -1.0f}, {0,1,0}, {0,0}},
                {{1.0f,  0.0f,  1.0f}, {0,1,0}, {1,1}},
                {{1.0f,  0.0f, -1.0f}, {0,1,0}, {0,1}},
                {{-1.0f, 0.0f,  1.0f}, {0,1,0}, {1,0}},
            };

            vertexSize = sizeof(Vertex);
            

            for (size_t i = 0; i < text.Length; i++) {

            }
            vertexCount = sizeof(quadVertices) / vertexSize * text.Length;  // not exactly the right length, but close enough
            vertices = ghnew Vertex[vertexCount];
            memcpy(vertices, quadVertices, vertexCount * vertexSize);

            indices = ghnew unsigned int[6] {
                0, 1, 2, // first triangle
                    0, 3, 1, // second triangle
            };
            indexCount = 6 * text.Length;

            return Mesh::init(graphics, commandList);
        }
	};
}