#include "Mesh.h"
#include "resource/ResourceContext.h"

namespace Ghurund {
    Status Mesh::loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption option) {
        if (Path) {
            if (Path->get().endsWith(ResourceFormat::OBJ.getExtension())) {
                return loadObj(context, stream);
            } else if (Path->get().endsWith(ResourceFormat::MESH.getExtension())) {
                return loadMesh(context, stream);
            } else {
                return Status::UNKNOWN_FORMAT;
            }
        }

        size_t bytesRead = stream.BytesRead;
        Status result = loadMesh(context, stream);
        if (result != Status::OK) {
            stream.set(bytesRead);
            result = loadObj(context, stream);
            if (result != Status::OK)
                return Status::UNKNOWN_FORMAT;
        }

        return result;
    }

    Status Mesh::loadObj(ResourceContext& context, MemoryInputStream& stream) {
        List<XMFLOAT3> objVerts;
        List<XMFLOAT3> objNorms;
        List<XMFLOAT2> objTexCoords;
        List<Vertex> triangleVertices;
        List<unsigned int> triangleIndices;

        ASCIIString obj((char*)stream.Data, stream.Size);
        List<ASCIIString> lines = obj.split("\n");
        for (ASCIIString& line : lines) {
            if (line.startsWith("#")) {
                continue;
            } else if (line.startsWith("v ")) {
                List<ASCIIString> vert = line.subString(2).trim().split(" ");
                XMFLOAT3 v((float)atof(vert[0]), (float)atof(vert[1]), -(float)atof(vert[2]));
                objVerts.add(v);
            } else if (line.startsWith("vt ")) {
                List<ASCIIString> vert = line.subString(2).trim().split(" ");
                XMFLOAT2 v((float)atof(vert[0]), 1 - (float)atof(vert[1]));
                objTexCoords.add(v);
            } else if (line.startsWith("vn ")) {
                List<ASCIIString> vert = line.subString(2).trim().split(" ");
                XMFLOAT3 v((float)atof(vert[0]), (float)atof(vert[1]), -(float)atof(vert[2]));
                objNorms.add(v);
            } else if (line.startsWith("f ")) {
                List<ASCIIString> vert = line.subString(2).trim().split(" ");

                triangleIndices.add((unsigned int)triangleVertices.Size);
                triangleIndices.add((unsigned int)(triangleVertices.Size + 2));
                triangleIndices.add((unsigned int)(triangleVertices.Size + 1));
                for (size_t j = 3; j < vert.Size; j++) {
                    triangleIndices.add((unsigned int)triangleVertices.Size);
                    triangleIndices.add((unsigned int)(j - 3 + triangleVertices.Size + 3));
                    triangleIndices.add((unsigned int)(j - 3 + triangleVertices.Size + 2));
                }
                for (size_t j = 0; j < vert.Size; j++) {
                    List<ASCIIString> face = vert[j].split("/");
                    Vertex v(objVerts[atoi(face[0]) - 1], objNorms[atoi(face[2]) - 1], objTexCoords[atoi(face[1]) - 1]);
                    triangleVertices.add(v);
                }
            }
        }

        vertexSize = sizeof(Vertex);
        vertexCount = (vindex_t)triangleVertices.Size;
        vertices = ghnew Vertex[vertexCount];
        memcpy(vertices, triangleVertices.begin(), vertexCount * vertexSize);

        indexCount = (vindex_t)triangleIndices.Size;
        indices = ghnew vindex_t[indexCount];
        memcpy(indices, triangleIndices.begin(), indexCount * sizeof(vindex_t));

        computeBoundingBox();

        return init(context.Graphics, context.CommandList);
    }

    Status Mesh::loadMesh(ResourceContext& context, MemoryInputStream& stream) {
        Status result = readHeader(stream);
        if (result != Status::OK)
            return result;

        vertexSize = sizeof(Vertex);
        vertexCount = stream.read<vindex_t>();
        vertices = ghnew Vertex[vertexCount];
        memcpy(vertices, stream.readBytes(vertexCount * vertexSize), vertexCount * vertexSize);

        indexCount = stream.read<vindex_t>();
        indices = ghnew vindex_t[indexCount];
        memcpy(indices, stream.readBytes(indexCount * sizeof(vindex_t)), indexCount * sizeof(vindex_t));

        XMFLOAT3 center = stream.read<XMFLOAT3>();
        XMFLOAT3 extents = stream.read<XMFLOAT3>();
        boundingBox = DirectX::BoundingBox(center, extents);

        return init(context.Graphics, context.CommandList);
    }

    Status Mesh::saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
        writeHeader(stream);

        stream.write<vindex_t>(vertexCount);
        stream.writeBytes(vertices, vertexCount * vertexSize);

        stream.write<vindex_t>(indexCount);
        stream.writeBytes(indices, indexCount * sizeof(vindex_t));

        stream.write<XMFLOAT3>(boundingBox.Center);
        stream.write<XMFLOAT3>(boundingBox.Extents);

        return Status::OK;
    }

    Mesh::~Mesh() {
        Valid = false;

        delete[] vertices;
        delete[] indices;
        vertexBuffer.ReleaseAndGetAddressOf();
        indexBuffer.ReleaseAndGetAddressOf();
        vertexUploadHeap.ReleaseAndGetAddressOf();
        indexUploadHeap.ReleaseAndGetAddressOf();
    }

    Status Mesh::init(Graphics& graphics, CommandList& commandList, unsigned int detail) {
        if (commandList.State == CommandListState::FINISHED)
            commandList.reset();

        {
            unsigned int vertexBufferSize = vertexSize * vertexCount;

            if (FAILED(graphics.Device->CreateCommittedResource(
                &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
                D3D12_HEAP_FLAG_NONE,
                &CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize),
                D3D12_RESOURCE_STATE_COPY_DEST,
                nullptr,
                IID_PPV_ARGS(&vertexBuffer)))) {
                return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("device->CreateCommittedResource() failed\n"));
            }

            if (FAILED(graphics.Device->CreateCommittedResource(
                &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
                D3D12_HEAP_FLAG_NONE,
                &CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize),
                D3D12_RESOURCE_STATE_GENERIC_READ,
                nullptr,
                IID_PPV_ARGS(&vertexUploadHeap)))) {
                return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("device->CreateCommittedResource() failed\n"));
            }

            D3D12_SUBRESOURCE_DATA vertexData = {};
            vertexData.pData = vertices;
            vertexData.RowPitch = vertexBufferSize;
            vertexData.SlicePitch = vertexBufferSize;

            // we are now creating a command with the command list to copy the data from
            // the upload heap to the default heap
            UpdateSubresources(commandList.get(), vertexBuffer.Get(), vertexUploadHeap.Get(), 0, 0, 1, &vertexData);

            commandList.get()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(vertexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER));

            vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
            vertexBufferView.StrideInBytes = sizeof(Vertex);
            vertexBufferView.SizeInBytes = vertexBufferSize;
        }

        commandList.addResourceRef(vertexUploadHeap.Get());
        commandList.addResourceRef(vertexBuffer.Get());

        {
            unsigned int indexBufferSize = sizeof(unsigned int) * indexCount;

            if (FAILED(graphics.Device->CreateCommittedResource(
                &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
                D3D12_HEAP_FLAG_NONE,
                &CD3DX12_RESOURCE_DESC::Buffer(indexBufferSize),
                D3D12_RESOURCE_STATE_COPY_DEST,
                nullptr,
                IID_PPV_ARGS(&indexBuffer)))) {
                return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("device->CreateCommittedResource() failed\n"));
            }

            if (FAILED(graphics.Device->CreateCommittedResource(
                &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
                D3D12_HEAP_FLAG_NONE,
                &CD3DX12_RESOURCE_DESC::Buffer(indexBufferSize),
                D3D12_RESOURCE_STATE_GENERIC_READ,
                nullptr,
                IID_PPV_ARGS(&indexUploadHeap)))) {
                return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("device->CreateCommittedResource() failed\n"));
            }

            D3D12_SUBRESOURCE_DATA indexData = {};
            indexData.pData = indices;
            indexData.RowPitch = indexBufferSize;
            indexData.SlicePitch = indexBufferSize;

            // we are now creating a command with the command list to copy the data from
            // the upload heap to the default heap
            UpdateSubresources(commandList.get(), indexBuffer.Get(), indexUploadHeap.Get(), 0, 0, 1, &indexData);

            commandList.get()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(indexBuffer.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER));

            indexBufferView.BufferLocation = indexBuffer->GetGPUVirtualAddress();
            indexBufferView.Format = DXGI_FORMAT_R32_UINT;
            indexBufferView.SizeInBytes = indexBufferSize;
        }

        commandList.addResourceRef(indexUploadHeap.Get());
        commandList.addResourceRef(indexBuffer.Get());
        commandList.finish();
        commandList.wait();

        Valid = true;

        return Status::OK;
    }

    void Mesh::draw(CommandList& commandList) {
        commandList.addPointerRef(this);
        ID3D12GraphicsCommandList* list = commandList.get();
        list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        list->IASetVertexBuffers(0, 1, &vertexBufferView);
        list->IASetIndexBuffer(&indexBufferView);
        list->DrawIndexedInstanced(indexCount, 1, 0, 0, 0);
    }

    void Mesh::removeDuplicates() {
        List<Vertex> vertexData;
        List<vindex_t> indexData;

        for (vindex_t i = 0; i < indexCount; i++) {
            Vertex& v = vertices[indices[i]];
            vindex_t index = (vindex_t)vertexData.Size;

            for (vindex_t j = 0; j < vertexData.Size; j++) {
                if (v.equals(vertexData[j], 0.01f, 0.01f, 0.01f)) {
                    index = j;
                    break;
                }
            }

            if (index == vertexData.Size)
                vertexData.add(v);
            indexData.add(index);
        }

        delete[] vertices;
        vertexCount = (vindex_t)vertexData.Size;
        vertices = ghnew Vertex[vertexCount];
        memcpy(vertices, vertexData.begin(), vertexCount * vertexSize);

        delete[] indices;
        indexCount = (vindex_t)indexData.Size;
        indices = ghnew vindex_t[indexCount];
        memcpy(indices, indexData.begin(), sizeof(vindex_t) * indexCount);
    }

    void Mesh::subdivide() {
        List<Vertex> vertexData;
        List<vindex_t> indexData;

        for (vindex_t i = 0, j = 0; i < indexCount; i += 3, j += 6) {
            Vertex v0 = vertices[indices[i]];
            Vertex v1 = vertices[indices[i + 1]];
            Vertex v2 = vertices[indices[i + 2]];

            Vertex v3 = (v0 + v1) / 2;
            Vertex v4 = (v1 + v2) / 2;
            Vertex v5 = (v0 + v2) / 2;

            vertexData.add(v0);
            vertexData.add(v1);
            vertexData.add(v2);
            vertexData.add(v3);
            vertexData.add(v4);
            vertexData.add(v5);

            indexData.add(j);
            indexData.add(j + 3);
            indexData.add(j + 5);

            indexData.add(j + 1);
            indexData.add(j + 4);
            indexData.add(j + 3);

            indexData.add(j + 2);
            indexData.add(j + 5);
            indexData.add(j + 4);

            indexData.add(j + 3);
            indexData.add(j + 4);
            indexData.add(j + 5);
        }

        vertexCount = (vindex_t)vertexData.Size;
        delete[] vertices;
        vertices = ghnew Vertex[vertexCount];
        memcpy(vertices, vertexData.begin(), vertexCount * vertexSize);

        indexCount = (vindex_t)indexData.Size;
        delete[] indices;
        indices = ghnew vindex_t[indexCount];
        memcpy(indices, indexData.begin(), indexCount * sizeof(vindex_t));
    }

    void Mesh::spherify() {
        for (vindex_t i = 0; i < vertexCount; i++) {
            Vertex& v = vertices[i];
            XMVECTOR pos = XMLoadFloat3(&v.position);
            XMStoreFloat3(&v.position, XMVector3Normalize(XMLoadFloat3(&v.position)));
        }
    }

    /*
    * smoothingTreshold maximum smooth angle in radians
    */
    void Mesh::generateSmoothing(float smoothingTreshold) {
        Vertex* newVertices = ghnew Vertex[indexCount * 3];
        for (size_t i = 0; i < indexCount; i++) {
            newVertices[i] = vertices[indices[i]];
            indices[i] = (vindex_t)i;
        }

        delete[] vertices;
        vertexCount = indexCount;
        vertices = newVertices;
    }

    void Mesh::generateNormals() {
        for (size_t i = 0; i < vertexCount; i++)
            vertices[i].normal = XMFLOAT3(0, 0, 0);
        for (size_t i = 0; i < indexCount; i += 3) {
            Vertex& v1 = vertices[indices[i]];
            Vertex& v2 = vertices[indices[i + 1]];
            Vertex& v3 = vertices[indices[i + 2]];
            XMVECTOR pos1 = XMLoadFloat3(&v1.position);
            XMVECTOR pos2 = XMLoadFloat3(&v2.position);
            XMVECTOR pos3 = XMLoadFloat3(&v3.position);
            XMVECTOR normal = XMVector3Normalize(XMVector3Cross(pos2 - pos1, pos3 - pos1));
            XMStoreFloat3(&v1.normal, XMLoadFloat3(&v1.normal) + normal);
            XMStoreFloat3(&v2.normal, XMLoadFloat3(&v2.normal) + normal);
            XMStoreFloat3(&v3.normal, XMLoadFloat3(&v3.normal) + normal);
        }
        for (size_t i = 0; i < vertexCount; i++)
            XMStoreFloat3(&vertices[i].normal, XMVector3Normalize(XMLoadFloat3(&vertices[i].normal)));
    }

    void Mesh::generateTangents() {}

    void Mesh::invertWinding() {
        for (size_t i = 0; i < vertexCount; i++) {
            Vertex& v = vertices[i];
            v.normal.z *= -1;
            v.tangent.z *= -1;
            v.position.z *= -1;
        }

        for (size_t i = 0; i < indexCount; i += 3) {
            vindex_t i0 = indices[i];
            vindex_t i1 = indices[i + 1];
            vindex_t i2 = indices[i + 2];
            indices[i] = i0;
            indices[i + 2] = i1;
            indices[i + 1] = i2;
        }
    }

    void Mesh::computeBoundingBox() {
        XMFLOAT3 min = {}, max = {};
        if (vertexCount > 0) {
            XMFLOAT3& pos = ((Vertex*)vertices)[0].position;
            min = pos;
            max = pos;
        }
        for (size_t i = 1; i < vertexCount; i++) {
            XMFLOAT3& pos = ((Vertex*)vertices)[i].position;
            min.x = std::min(pos.x, min.x);
            min.y = std::min(pos.y, min.y);
            min.z = std::min(pos.z, min.z);
            max.x = std::max(pos.x, max.x);
            max.y = std::max(pos.y, max.y);
            max.z = std::max(pos.z, max.z);
        }
        XMFLOAT3 center = XMFLOAT3((min.x + max.x) / 2, (min.y + max.y) / 2, (min.z + max.z) / 2);
        XMFLOAT3 extents = XMFLOAT3(center.x - min.x, center.y - min.y, center.z - min.z);
        boundingBox = DirectX::BoundingBox(center, extents);
    }

    bool Mesh::intersects(XMFLOAT3& pos, XMFLOAT3& dir, float& dist) {
        XMVECTOR pos2 = XMLoadFloat3(&pos);
        XMVECTOR dir2 = XMLoadFloat3(&dir);
        for (size_t i = 0; i < indexCount / 3; i++) {
            Vertex& v0 = vertices[indices[i]];
            Vertex& v1 = vertices[indices[i + 1]];
            Vertex& v2 = vertices[indices[i + 2]];
            if (TriangleTests::Intersects(pos2, dir2, XMLoadFloat3(&v0.position), XMLoadFloat3(&v1.position), XMLoadFloat3(&v2.position), dist))
                return true;
        }
        return false;
    }
}