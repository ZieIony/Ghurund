#pragma once

#include "ui/UIContext.h"

namespace Ghurund::Core {
    class Window;
}

namespace UnitTest {
    using namespace Ghurund::UI;

    class TestUIContext:public Ghurund::UI::UIContext {
    public:
        TestUIContext(
            Ghurund::Core::Window& window
        ):UIContext(window) {}

        virtual Resource* makeControlMesh() override;

        virtual Resource* makeTextMesh(const WString& text, const Font& font) override;
    };
}
