#pragma once

#include "ui/UIContext.h"

namespace Ghurund::Core {
    class Window;
}

namespace UnitTest {
    class TestUIContext:public Ghurund::UI::IUIContext {
    public:
        TestUIContext(
            Ghurund::Core::Window& window
        ):IUIContext(window) {}
    };
}
