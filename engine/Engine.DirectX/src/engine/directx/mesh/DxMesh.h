#pragma once

#include "core/resource/Resource.h"
#include "core/resource/ResourceManager.h"
#include "engine/directx/CommandList.h"
#include "engine/directx/memory/DxGPUMemoryManager.h"
#include "engine/graphics/mesh/MeshData.h"
#include "engine/graphics/mesh/Mesh.h"

#pragma warning(push, 0)
#include <d3d12.h>
#pragma warning(pop)

#include <wrl.h>

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

    private:
        virtual void onDeinit() override {
            roles.clear();
            vertexBuffers.clear();
            vertexBuffersView.clear();
            indexBuffer.Reset();
        }

        virtual void updateDataSize() {
            dataSize.system = sizeof(*this);
            if (meshData != nullptr)
                meshData->getDataSize();
            dataSize.graphical = 0;
        }

    protected:
        List<ShaderInputSemanticEnum> roles;
        List<ComPtr<ID3D12Resource>> vertexBuffers;
        List<D3D12_VERTEX_BUFFER_VIEW> vertexBuffersView;

        DxGPUMemoryManager* memoryManager;
        ComPtr<ID3D12Resource> idBuffer;
        D3D12_VERTEX_BUFFER_VIEW idBufferView;

        ComPtr<ID3D12Resource> indexBuffer;
        D3D12_INDEX_BUFFER_VIEW indexBufferView;
        uint32_t indexCount = 0;

        void initVertexBuffers(const Array<VertexStream>& vertexStreams, uint32_t vertexCount, DxGPUMemoryManager& memoryManager);

        void initIndexBuffer(const Buffer& indices, uint32_t indexCount, DxGPUMemoryManager& memoryManager);

    public:
        // VS complains
        DxMesh() {}

        // TODO: move this to coroutines
        void init(DxGPUMemoryManager& memoryManager);

        void draw(CommandList& commandList, const Array<ShaderInputSemanticEnum>& layout, const List<uint32_t>& ids);
    };
}
