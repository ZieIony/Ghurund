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
            IGraphicsResourceFactory& resourceFactory
        ):UIContext(window, textMeshFactory, resourceFactory) {}

        virtual Mesh* makeControlMesh() override;
    };
}
