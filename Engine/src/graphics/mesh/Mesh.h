#pragma once

#include "Ghurund.h"
#include "core/Logger.h"
#include "graphics/Fence.h"
#include "graphics/Graphics.h"
#include "graphics/CommandList.h"
#include "Vertex.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include "d3dx12.h"
#include "resource/Resource.h"
#include "resource/ResourceManager.h"

#include <wrl.h>
#include <DirectXCollision.h>

using namespace DirectX;
using namespace Microsoft::WRL;

namespace Ghurund {
    typedef UINT32 vindex_t;

    class Mesh:public Resource {
    protected:
        Vertex *vertices = nullptr;
        unsigned int vertexSize;
        vindex_t vertexCount;
        vindex_t *indices = nullptr;
        vindex_t indexCount;

        ComPtr<ID3D12Resource> vertexBuffer;
        D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
        ComPtr<ID3D12Resource> indexBuffer;
        D3D12_INDEX_BUFFER_VIEW indexBufferView;

        ComPtr<ID3D12Resource> vertexUploadHeap;
        ComPtr<ID3D12Resource> indexUploadHeap;

        BoundingBox boundingBox;

        virtual Status loadInternal(ResourceManager &resourceManager, ResourceContext &context, MemoryInputStream &stream, LoadOption option);

        Status loadObj(ResourceContext &context, MemoryInputStream &stream);
        Status loadMesh(ResourceContext &context, MemoryInputStream &stream);

        virtual Status saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options) const;

        virtual unsigned int getVersion()const {
            return 1;
        }

        vindex_t findVertex(Vertex &vertex) {
            for(vindex_t i = 0; i<vertexCount; i++) {
                if(vertex.equals(vertices[i], 0.01f, 0.01f, 0.01f))
                    return i;
            }
            return vertexCount;
        }

    public:
        ~Mesh() {
            delete[] vertices;
            delete[] indices;
            vertexBuffer.Reset();
            indexBuffer.Reset();
            vertexUploadHeap.Reset();
            indexUploadHeap.Reset();
        }

        Status init(Graphics &graphics, CommandList &commandList);

        void draw(CommandList &commandList) {
            ID3D12GraphicsCommandList *list = commandList.get();
            list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            list->IASetVertexBuffers(0, 1, &vertexBufferView);
            list->IASetIndexBuffer(&indexBufferView);
            list->DrawIndexedInstanced(indexCount, 1, 0, 0, 0);
        }

        void removeDuplicates() {
            List<Vertex> vertexData;
            List<vindex_t> indexData;

            for(vindex_t i = 0; i<indexCount; i++) {
                vindex_t index = findVertex(vertices[indices[i]]);
                if(index==indices[i])
                    vertexData.add(vertices[index]);
                indexData.add(index);
            }

            memcpy(vertices, vertexData.begin(), vertexData.Size*vertexSize);
            vertexCount = vertexData.Size;
            memcpy(indices, indexData.begin(), sizeof(vindex_t)*indexData.Size);
            indexCount = indexData.Size;
        }

        void subdivide() {
            List<Vertex> vertexData;
            List<vindex_t> indexData;

            for(vindex_t i = 0, j = 0; i<indexCount; i += 3, j += 6) {
                Vertex v0 = vertices[indices[i]];
                Vertex v1 = vertices[indices[i+1]];
                Vertex v2 = vertices[indices[i+2]];

                Vertex v3 = (v0+v1)/2;
                Vertex v4 = (v1+v2)/2;
                Vertex v5 = (v0+v2)/2;

                vertexData.add(v0);
                vertexData.add(v1);
                vertexData.add(v2);
                vertexData.add(v3);
                vertexData.add(v4);
                vertexData.add(v5);

                indexData.add(j);
                indexData.add(j+3);
                indexData.add(j+5);

                indexData.add(j+1);
                indexData.add(j+4);
                indexData.add(j+3);

                indexData.add(j+2);
                indexData.add(j+5);
                indexData.add(j+4);

                indexData.add(j+3);
                indexData.add(j+4);
                indexData.add(j+5);
            }

            vertexCount = vertexData.Size;
            delete[] vertices;
            vertices = ghnew Vertex[vertexCount];
            memcpy(vertices, vertexData.begin(), vertexCount*vertexSize);

            indexCount = indexData.Size;
            delete[] indices;
            indices = ghnew vindex_t[indexCount];
            memcpy(indices, indexData.begin(), indexCount*sizeof(vindex_t));
        }

        void spherify() {
            for(vindex_t i = 0; i<vertexCount; i++) {
                Vertex &v = vertices[i];
                XMVECTOR pos = XMLoadFloat3(&v.position);
                XMStoreFloat3(&v.position, XMVector3Normalize(XMLoadFloat3(&v.position)));
            }
        }

        void generateNormals(float smoothingTreshold);
        void generateTangents();
        void invertWinding();
        void computeBoundingBox();

        BoundingBox &getBoundingBox() {
            return boundingBox;
        }

        __declspec(property(get = getBoundingBox)) BoundingBox &BoundingBox;

        virtual const Ghurund::Type &getType() const override {
            return Type::MESH;
        }

        virtual const Array<ResourceFormat> &getFormats() const override {
            static const Array<ResourceFormat> formats = {ResourceFormat::AUTO, ResourceFormat::MESH, ResourceFormat::OBJ};
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::MESH;
        }

        virtual bool intersects(XMFLOAT3 &pos, XMFLOAT3 &dir) {
            float dist;
            XMVECTOR pos2 = XMLoadFloat3(&pos);
            XMVECTOR dir2 = XMLoadFloat3(&dir);
            for(size_t i = 0; i<indexCount/3; i++) {
                Vertex &v0 = vertices[indices[i]];
                Vertex &v1 = vertices[indices[i+1]];
                Vertex &v2 = vertices[indices[i+2]];
                if(TriangleTests::Intersects(pos2, dir2, XMLoadFloat3(&v0.position), XMLoadFloat3(&v1.position), XMLoadFloat3(&v2.position), dist))
                    return true;
            }
            return false;
        }
    };
}