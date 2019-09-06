#pragma once

#include "application/Logger.h"
#include "graphics/Fence.h"
#include "graphics/Graphics.h"
#include "graphics/CommandList.h"
#include "Vertex.h"
#include "resource/Resource.h"
#include "resource/ResourceManager.h"

#pragma warning(push, 0)
#include <d3d12.h>
#include <dxgi1_4.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include "d3dx12.h"
#include <DirectXCollision.h>

#include <wrl.h>

#include <PxShape.h>
#pragma warning(pop)

namespace Ghurund {
    using namespace DirectX;
    using namespace Microsoft::WRL;
    using namespace physx;

    typedef uint32_t vindex_t;

    class Mesh:public Resource {
	private:
		inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<Mesh>();

    protected:
        void* vertices = nullptr;
        unsigned int vertexSize;
        vindex_t vertexCount;
        vindex_t* indices = nullptr;
        vindex_t indexCount;

        ComPtr<ID3D12Resource> vertexBuffer;
        D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
        ComPtr<ID3D12Resource> indexBuffer;
        D3D12_INDEX_BUFFER_VIEW indexBufferView;

        ComPtr<ID3D12Resource> vertexUploadHeap;
        ComPtr<ID3D12Resource> indexUploadHeap;

        BoundingBox boundingBox;
		PxGeometry* geometry;

        virtual Status loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption option);

        Status loadObj(ResourceContext& context, MemoryInputStream& stream);
        Status loadMesh(ResourceContext& context, MemoryInputStream& stream);

        virtual Status saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const;

        virtual unsigned int getVersion()const {
            return 1;
        }

    public:
        ~Mesh();

        virtual Status init(Graphics& graphics, CommandList& commandList, unsigned int detail = 0);

        void draw(CommandList& commandList);

        void removeDuplicates();
        void subdivide();
        void spherify();
        void generateSmoothing(float smoothingTreshold);
        void generateNormals();
        void generateTangents();
        void invertWinding();
        void computeBoundingBox();

        virtual bool intersects(XMFLOAT3& pos, XMFLOAT3& dir, float& dist);

        PxGeometry &getGeometry() {
            return *geometry;
        }

		__declspec(property(get = getGeometry)) PxGeometry& Geometry;

        vindex_t getVertexCount() const {
            return vertexCount;
        }

        __declspec(property(get = getVertexCount)) vindex_t VertexCount;

        vindex_t getIndexCount() const {
            return indexCount;
        }

        __declspec(property(get = getIndexCount)) vindex_t IndexCount;

        BoundingBox& getBoundingBox() {
            return boundingBox;
        }

        __declspec(property(get = getBoundingBox)) BoundingBox& BoundingBox;

		inline static const Ghurund::Type& TYPE = Ghurund::Type(CONSTRUCTOR, "Ghurund", "Mesh");

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        static const Array<ResourceFormat*>& getFormats() {
            static const Array<ResourceFormat*> formats = {(ResourceFormat*)& ResourceFormat::MESH, (ResourceFormat*)& ResourceFormat::OBJ};
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*>& Formats;
    };
}