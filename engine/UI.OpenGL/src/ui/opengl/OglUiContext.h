#pragma once

#include "ui/UIContext.h"

namespace Ghurund::Core {
    class ResourceManager;
    class Window;
}

namespace Ghurund::UI::OpenGL {
    using namespace Ghurund::Core;

    class OglUiContext:public UIContext {
    public:
        OglUiContext(
            Ghurund::Core::Window& window,
            ITextMeshFactory& textMeshFactory,
            ITextureFactory& textureFactory
        ):UIContext(window, textMeshFactory, textureFactory) {}

        virtual Resource* makeControlMesh() override;
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::OpenGL::OglUiContext>();
}