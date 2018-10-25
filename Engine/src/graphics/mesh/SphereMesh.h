#pragma once

#include "Mesh.h"
#include "resource/ResourceManager.h"

namespace Ghurund {
	class SphereMesh : public Mesh {
	protected:
        Status init(Graphics &graphics, CommandList &commandList) {
			Vertex triangleVertices[] = {
				{ { 0.0f,  1.0f, 0.0f },{ 0.0f, 0.0f } },
				{ { sqrtf(8.0f/9.0f),  -1.0f/3.0f, 0 },{0.0f, 1.0f } },
				{ {-sqrtf(2.0f/9.0f),  -1.0f/3.0f, sqrt(2.0f/3.0f)},{ 0.3333f, 1.0f } },
				{ {-sqrtf(2.0f/9.0f),  -1.0f/3.0f, -sqrt(2.0f/3.0f)}, {0.6667f, 1.0f } }
			};

			vertexSize = sizeof(Vertex);
			vertexCount = sizeof(triangleVertices) / vertexSize;
			vertices = ghnew BYTE[vertexCount*vertexSize];
			memcpy(vertices, triangleVertices, vertexCount*vertexSize);

			indices = ghnew unsigned int[12]{
                0,2,1,
                0,3,2,
                0,1,3,
                1,2,3
			};
			indexCount = 12;

            /*if(size<5) {
                subdivide<Vertex>();
                removeDuplicates<Vertex>();
                spherify();
            }*/

			return Mesh::init(graphics, commandList);
		}
	};
}