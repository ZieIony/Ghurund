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
        auto mesh = makeIntrusive<DxMesh>();
        auto meshData = makeIntrusive<QuadMeshData>();
        meshData->init();
        mesh->Data = meshData.get();
        mesh->init(memoryManager);
        this->mesh = mesh;
    }

    Mesh* DxUIContext::makeControlMesh() {
        return mesh.get();
    }
}
