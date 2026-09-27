#include "ghuidxpch.h"
#include "DxUIContext.h"

#include "engine/directx/mesh/DxMesh.h"
#include "engine/graphics/mesh/QuadMeshData.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::DirectX::DxUIContext>() {
        static Type TYPE = TypeBuilder<Ghurund::UI::DirectX::DxUIContext>();
        return TYPE;
    }
}

namespace Ghurund::UI::DirectX {
    using namespace Ghurund::Engine::DirectX;

    DxUIContext::DxUIContext(
        ::Ghurund::Core::Window& window,
        DxGPUMemoryManager& memoryManager,
        ITextMeshFactory& textMeshFactory,
        class IGraphicsResourceFactory& resourceFactory
    ):UIContext(window, textMeshFactory, resourceFactory), memoryManager(memoryManager) {
        auto mesh = ghnew DxMesh();
        auto meshData = ghnew QuadMeshData();
        meshData->init();
        mesh->init(*meshData, memoryManager);
        meshData->release();
        this->mesh.set(mesh);
    }

    Mesh* DxUIContext::makeControlMesh() {
        return mesh.get();
    }
}
