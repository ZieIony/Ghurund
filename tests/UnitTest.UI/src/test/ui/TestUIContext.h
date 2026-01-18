#pragma once

#include "engine/graphics/mesh/Mesh.h"
#include "ui/UIContext.h"

namespace Ghurund::Core {
    class Window;
}

namespace UnitTest {
    using namespace Ghurund::UI;

    class TestUIContext:public Ghurund::UI::UIContext {
    public:
        TestUIContext(
            Ghurund::Core::Window& window,
            ITextMeshFactory& textMeshFactory,
            ITextureFactory& textureFactory
        ):UIContext(window, textMeshFactory, textureFactory) {}

        virtual Mesh* makeControlMesh() override;
    };
}
