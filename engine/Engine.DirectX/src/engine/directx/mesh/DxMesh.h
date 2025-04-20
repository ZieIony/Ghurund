#pragma once

#include "engine/directx/Fence.h"
#include "engine/directx/Graphics.h"
#include "engine/directx/CommandList.h"
#include "core/resource/Resource.h"
#include "core/resource/ResourceManager.h"
#include "graphics/mesh/Mesh.h"

#pragma warning(push, 0)
#include <d3d12.h>
#include <dxgi1_4.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include "d3dx12.h"
#include <DirectXCollision.h>

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

        Array<ComPtr<ID3D12Resource>> vertexBuffer;
        Array<D3D12_VERTEX_BUFFER_VIEW> vertexBufferView;
        ComPtr<ID3D12Resource> indexBuffer;
        D3D12_INDEX_BUFFER_VIEW indexBufferView;

        Array<ComPtr<ID3D12Resource>> vertexUploadHeap;
        ComPtr<ID3D12Resource> indexUploadHeap;

        virtual unsigned int getVersion()const {
            return 1;
        }

    public:
        virtual void init(Graphics& graphics, CommandList& commandList, unsigned int detail = 0);

        void initVertexBuffers(Graphics& graphics, CommandList& commandList);

        void initIndexBuffer(Graphics& graphics, CommandList& commandList);

        virtual void invalidate() override {
            uploaded = false;
            for(auto& buffer:vertexBuffer)
                buffer.Reset();
            indexBuffer.Reset();
            for(auto& heap:vertexUploadHeap)
                heap.Reset();
            indexUploadHeap.Reset();

            __super::invalidate();
        }

        virtual bool isValid() const override {
			return __super::isValid() && vertexBuffer[0].Get() && indexBuffer.Get() && uploaded;
        }

        void draw(CommandList& commandList);

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return Mesh::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_MESH = ResourceFormat(L"mesh", true, true);
        static const inline ResourceFormat FORMAT_OBJ = ResourceFormat(L"obj", true, false);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_MESH, FORMAT_OBJ };
#pragma endregion
    };
}