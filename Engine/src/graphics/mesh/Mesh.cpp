#include "Mesh.h"

namespace Ghurund {
    Status Mesh::loadObj(ResourceManager & resourceManager, const void * data, unsigned long size, unsigned long * bytesRead) {
        List<XMFLOAT3> objVerts;
        List<XMFLOAT3> objNorms;
        List<XMFLOAT2> objTexCoords;
        List<Vertex> triangleVertices;
        List<unsigned int> triangleIndices;

        ASCIIString obj((const char*)data, size);
        List<ASCIIString> lines = obj.split("\n");
        for(size_t i = 0; i<lines.Size; i++) {
            ASCIIString &line = lines[i];
            if(line.startsWith("#")) {
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
                for(size_t j = 3; j<vert.Size; j++) {
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

        if(bytesRead!=nullptr)
            *bytesRead = size;

        return init(resourceManager.getGraphics(), resourceManager.getCommandList());
    }

    Status Mesh::init(Graphics &graphics, shared_ptr<CommandList> commandList) {
        {
            unsigned int vertexBufferSize = vertexSize*vertexCount;

            if(FAILED(graphics.Device->CreateCommittedResource(
                &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
                D3D12_HEAP_FLAG_NONE,
                &CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize),
                D3D12_RESOURCE_STATE_COPY_DEST,
                nullptr,
                IID_PPV_ARGS(&vertexBuffer)))) {
                Logger::log(_T("device->CreateCommittedResource() failed\n"));
                return Status::CALL_FAIL;
            }

            if(FAILED(graphics.Device->CreateCommittedResource(
                &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
                D3D12_HEAP_FLAG_NONE,
                &CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize),
                D3D12_RESOURCE_STATE_GENERIC_READ,
                nullptr,
                IID_PPV_ARGS(&vertexUploadHeap)))) {
                Logger::log(_T("device->CreateCommittedResource() failed\n"));
                return Status::CALL_FAIL;
            }

            D3D12_SUBRESOURCE_DATA vertexData = {};
            vertexData.pData = vertices;
            vertexData.RowPitch = vertexBufferSize;
            vertexData.SlicePitch = vertexBufferSize;

            // we are now creating a command with the command list to copy the data from
            // the upload heap to the default heap
            UpdateSubresources(commandList->get(), vertexBuffer.Get(), vertexUploadHeap.Get(), 0, 0, 1, &vertexData);

            commandList->get()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(vertexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER));

            vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
            vertexBufferView.StrideInBytes = sizeof(Vertex);
            vertexBufferView.SizeInBytes = vertexBufferSize;
        }

        {
            unsigned int indexBufferSize = sizeof(unsigned int)*indexCount;

            if(FAILED(graphics.Device->CreateCommittedResource(
                &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
                D3D12_HEAP_FLAG_NONE,
                &CD3DX12_RESOURCE_DESC::Buffer(indexBufferSize),
                D3D12_RESOURCE_STATE_COPY_DEST,
                nullptr,
                IID_PPV_ARGS(&indexBuffer)))) {
                Logger::log(_T("device->CreateCommittedResource() failed\n"));
                return Status::CALL_FAIL;
            }

            if(FAILED(graphics.Device->CreateCommittedResource(
                &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
                D3D12_HEAP_FLAG_NONE,
                &CD3DX12_RESOURCE_DESC::Buffer(indexBufferSize),
                D3D12_RESOURCE_STATE_GENERIC_READ,
                nullptr,
                IID_PPV_ARGS(&indexUploadHeap)))) {
                Logger::log(_T("device->CreateCommittedResource() failed\n"));
                return Status::CALL_FAIL;
            }

            D3D12_SUBRESOURCE_DATA indexData = {};
            indexData.pData = indices;
            indexData.RowPitch = indexBufferSize;
            indexData.SlicePitch = indexBufferSize;

            // we are now creating a command with the command list to copy the data from
            // the upload heap to the default heap
            UpdateSubresources(commandList->get(), indexBuffer.Get(), indexUploadHeap.Get(), 0, 0, 1, &indexData);

            commandList->get()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(indexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER));

            indexBufferView.BufferLocation = indexBuffer->GetGPUVirtualAddress();
            indexBufferView.Format = DXGI_FORMAT_R32_UINT;
            indexBufferView.SizeInBytes = indexBufferSize;
        }

        return Status::OK;
    }

    void Mesh::generateNormals(float smoothingTreshold){
	}

	void Mesh::generateTangents(){
	}

	void Mesh::invertWinding() {
	}
}