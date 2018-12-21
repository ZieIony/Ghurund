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

    public:
        ~Mesh();

        virtual Status init(Graphics &graphics, CommandList &commandList);

        void draw(CommandList &commandList);

        void removeDuplicates();
        void subdivide();
        void spherify();
        void generateSmoothing(float smoothingTreshold);
        void generateNormals();
        void generateTangents();
        void invertWinding();
        void computeBoundingBox();

        virtual bool intersects(XMFLOAT3 &pos, XMFLOAT3 &dir);

        BoundingBox &getBoundingBox() {
            return boundingBox;
        }

        __declspec(property(get = getBoundingBox)) BoundingBox &BoundingBox;

        virtual const Ghurund::Type &getType() const override {
            return Type::MESH;
        }

        static const Array<ResourceFormat*> &getFormats() {
            static const Array<ResourceFormat*> formats = {(ResourceFormat*)&ResourceFormat::MESH, (ResourceFormat*)&ResourceFormat::OBJ};
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*> &Formats;
    };
}