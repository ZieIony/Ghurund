#pragma once

#include "graphics/mesh/Mesh.h"
#include "resource/ResourceManager.h"

namespace Ghurund {
    class ObjMesh: public Mesh {
    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size) {
            List<XMFLOAT3> objVerts;
            List<XMFLOAT3> objNorms;
            List<XMFLOAT2> objTexCoords;
            List<Vertex> triangleVertices;
            List<unsigned int> triangleIndices;

            ASCIIString obj((const char*)data, size);
            List<ASCIIString> lines = obj.split("\n");
            for(size_t i = 0; i<lines.Size; i++) {
                ASCIIString &line = lines[i];
				if (line.startsWith("#")) {
					continue;
				} else if(line.startsWith("v ")) {
                    List<ASCIIString> vert = line.subString(2).trim().split(" ");
                    XMFLOAT3 v((float)atof(vert[0]), (float)atof(vert[1]), -(float)atof(vert[2]));
                    objVerts.add(v);
                } else if(line.startsWith("vt ")) {
                    List<ASCIIString> vert = line.subString(2).trim().split(" ");
                    XMFLOAT2 v((float)atof(vert[0]), 1-(float)atof(vert[1]));
                    objTexCoords.add(v);
                } else if(line.startsWith("vn ")) {
                    List<ASCIIString> vert = line.subString(2).trim().split(" ");
                    XMFLOAT3 v((float)atof(vert[0]), (float)atof(vert[1]), -(float)atof(vert[2]));
                    objNorms.add(v);
                } else if(line.startsWith("f ")) {
                    List<ASCIIString> vert = line.subString(2).trim().split(" ");

                    triangleIndices.add(triangleVertices.Size);
                    triangleIndices.add(triangleVertices.Size+2);
                    triangleIndices.add(triangleVertices.Size+1);
					for(size_t j=3;j<vert.Size;j++){
                        triangleIndices.add(triangleVertices.Size);
                        triangleIndices.add(j-3+triangleVertices.Size+3);
                        triangleIndices.add(j-3+triangleVertices.Size+2);
                    }
                    for(size_t j = 0; j<vert.Size; j++) {
                        List<ASCIIString> face = vert[j].split("/");
                        Vertex v(objVerts[atoi(face[0])-1], objNorms[atoi(face[2])-1], objTexCoords[atoi(face[1])-1]);
                        triangleVertices.add(v);
                    }
                }
            }

            vertexSize = sizeof(Vertex);
            vertexCount = triangleVertices.Size;
            vertices = ghnew BYTE[vertexCount*vertexSize];
            memcpy(vertices, triangleVertices.begin(), vertexCount*vertexSize);

            indexCount = triangleIndices.Size;
            indices = ghnew unsigned int[indexCount];
            memcpy(indices, triangleIndices.begin(), indexCount*sizeof(unsigned int));

            return Mesh::init(resourceManager.getGraphics(), resourceManager.getCommandList());
        }

        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size, unsigned int flags = 0)const {
            return Status::NOT_IMPLEMENTED;
        }

    };
}