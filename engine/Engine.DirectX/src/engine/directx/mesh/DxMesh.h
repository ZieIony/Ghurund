#pragma once

#include "core/resource/Resource.h"
#include "core/resource/ResourceManager.h"
#include "engine/directx/CommandList.h"
#include "engine/directx/Fence.h"
#include "engine/directx/memory/DxGPUMemoryManager.h"
#include "engine/graphics/mesh/MeshData.h"
#include "engine/graphics/mesh/Mesh.h"

#pragma warning(push, 0)
#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include "d3dx12.h"

#include <wrl.h>
#pragma warning(pop)

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Engine;
    using namespace DirectX;
    using namespace Microsoft::WRL;

    class DxMesh:public Mesh {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = DxMesh::GET_TYPE();
#pragma endregion

    protected:
        bool uploaded = false;

        List<VertexRole> roles;
        List<ComPtr<ID3D12Resource>> vertexBuffers;
        List<D3D12_VERTEX_BUFFER_VIEW> vertexBuffersView;

        ComPtr<ID3D12Resource> indexBuffer;
        D3D12_INDEX_BUFFER_VIEW indexBufferView;
        uint32_t indexCount;

        void initVertexBuffers(const Array<VertexStream>& vertexStreams, uint32_t vertexCount, DxGPUMemoryManager& memoryManager);

        void initIndexBuffer(const Buffer& indices, uint32_t indexCount, DxGPUMemoryManager& memoryManager);

    public:
        virtual void init(const MeshData& mesh, DxGPUMemoryManager& memoryManager);

        virtual void invalidate() override {
            uploaded = false;
            vertexBuffers.clear();
            vertexBuffersView.clear();
            /*for(auto& buffer:vertexBuffers)
                buffer.Reset();*/
            indexBuffer.Reset();

            __super::invalidate();
        }

        virtual bool isValid() const override {
			return __super::isValid() && vertexBuffers[0].Get() && indexBuffer.Get() && uploaded;
        }

        void draw(CommandList& commandList, const Array<VertexRole>& layout);

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return DxMesh::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_MESH = ResourceFormat(L"mesh", ResourceFormatOptions::CAN_LOAD);
        static const inline ResourceFormat FORMAT_OBJ = ResourceFormat(L"obj", ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_MESH, FORMAT_OBJ };

        static const inline uint32_t VERSION = 1;
#pragma endregion
    };
}