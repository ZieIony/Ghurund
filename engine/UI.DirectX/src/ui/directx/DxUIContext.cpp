#include "ghuidxpch.h"
#include "DxUIContext.h"

#include "engine/directx/CommandList.h"
#include "engine/directx/DxGraphics.h"
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
        DxGraphics& graphics,
        CommandList& commandList
    ):UIContext(window), graphics(graphics), commandList(commandList) {
        auto mesh = ghnew DxMesh();
        auto meshData = ghnew QuadMeshData();
        meshData->init();
        mesh->init(*meshData, graphics, commandList);
        meshData->release();
        this->mesh.set(mesh);
    }

    Resource* DxUIContext::makeControlMesh() {
        return mesh.get();
    }

    Resource* DxUIContext::makeTextMesh(const WString& text, const Font& font) {
        return nullptr;
    }
}