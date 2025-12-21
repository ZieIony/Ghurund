#pragma once

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
        DxGraphics& graphics;
        CommandList& commandList;
        IntrusivePointer<Resource> mesh;

    public:
        DxUIContext(
            ::Ghurund::Core::Window& window,
            DxGraphics& graphics,
            CommandList& commandList,
            ITextMeshFactory& textMeshFactory,
            ITextureFactory& textureFactory
        );

        virtual Resource* makeControlMesh() override;
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::DirectX::DxUIContext>();
}