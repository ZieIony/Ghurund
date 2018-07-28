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

using namespace DirectX;
using namespace Microsoft::WRL;

namespace Ghurund {
    typedef UINT32 vindex_t;

    class Mesh:public Resource {
    protected:
        void *vertices = nullptr;
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

        virtual Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned long *bytesRead) {
            return loadObj(resourceManager, data, size, bytesRead);
        }

        Status loadObj(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned long *bytesRead);

        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size)const {
            return Status::NOT_IMPLEMENTED;
        }

        virtual unsigned int getVersion()const {
            return 0;
        }

        virtual void clean() {
            delete[] vertices;
            vertices = nullptr;
            delete[] indices;
            indices = nullptr;
            vertexBuffer.Reset();
            vertexBufferView = {};
            indexBuffer.Reset();
            indexBufferView = {};
            vertexUploadHeap.Reset();
            indexUploadHeap.Reset();
        }

        template<class Type> vindex_t findVertex(Type *vertex) {
            for(vindex_t i = 0; i<vertexCount; i++) {
                if(vertex->equals(*((Type*)vertices+i),0.01f,0.01f,0.01f))
                    return i;
            }
            return vertexCount;
        }

    public:
        ~Mesh() {
            clean();
        }

        Status init(Graphics &graphics, std::shared_ptr<CommandList> commandList);

        void draw(ID3D12GraphicsCommandList *commandList) {
            commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
            commandList->IASetVertexBuffers(0, 1, &vertexBufferView);
            commandList->IASetIndexBuffer(&indexBufferView);
            commandList->DrawIndexedInstanced(indexCount, 1, 0, 0, 0);
        }

        template<class Type> void removeDuplicates() {
            List<Type> vertexData;
            List<vindex_t> indexData;

            for(vindex_t i = 0; i<indexCount; i++) {
                vindex_t index = findVertex((Type*)vertices+indices[i]);
                if(index==indices[i])
                    vertexData.add(*((Type*)vertices+index));
                indexData.add(index);
            }

            memcpy(vertices, vertexData.begin(), vertexData.Size*vertexSize);
            vertexCount = vertexData.Size;
            memcpy(indices, indexData.begin(), sizeof(vindex_t)*indexData.Size);
            indexCount = indexData.Size;
        }

        template<class Type> void subdivide() {
            List<Type> vertexData;
            List<vindex_t> indexData;

            for(vindex_t i = 0, j = 0; i<indexCount; i += 3, j += 6) {
                Type v0 = *((Type*)vertices+indices[i]);
                Type v1 = *((Type*)vertices+indices[i+1]);
                Type v2 = *((Type*)vertices+indices[i+2]);

                Type v3 = (v0+v1)/2;
                Type v4 = (v1+v2)/2;
                Type v5 = (v0+v2)/2;

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
            vertices = ghnew Type[vertexCount];
            memcpy(vertices, vertexData.begin(), vertexCount*vertexSize);

            indexCount = indexData.Size;
            delete[] indices;
            indices = ghnew vindex_t[indexCount];
            memcpy(indices, indexData.begin(), indexCount*sizeof(vindex_t));
        }

        void spherify() {
            for(vindex_t i = 0; i<vertexCount; i++) {
                Vertex *v = (Vertex*)vertices+i;
                XMVECTOR pos = XMLoadFloat3(&v->position);
                XMStoreFloat3(&v->position, XMVector3Normalize(XMLoadFloat3(&v->position)));
            }
        }

		void generateNormals(float smoothingTreshold);
		void generateTangents();
		void invertWinding();

        virtual const Array<ResourceFormat> &getFormats() const override {
            static const Array<ResourceFormat> formats = {ResourceFormat::AUTO, ResourceFormat::MESH, ResourceFormat::OBJ};
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::MESH;
        }
    };
}