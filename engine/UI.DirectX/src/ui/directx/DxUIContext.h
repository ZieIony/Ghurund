#pragma once

#include "engine/directx/memory/DxGPUMemoryManager.h"
#include "ui/UIContext.h"

namespace Ghurund::Core {
    class ResourceManager;
    class Window;
}

namespace Ghurund::Engine::DirectX {
    class DxGraphics;
    class CommandList;
}

namespace Ghurund::UI::DirectX {
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine::DirectX;

    class DxUIContext:public UIContext {
    private:
        DxGPUMemoryManager& memoryManager;
        IntrusivePointer<Mesh> mesh;

    public:
        DxUIContext(
            ::Ghurund::Core::Window& window,
            DxGPUMemoryManager& memoryManager,
            ITextMeshFactory& textMeshFactory,
            ITextureFactory& textureFactory
        );

        virtual Mesh* makeControlMesh() override;
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::DirectX::DxUIContext>();
}