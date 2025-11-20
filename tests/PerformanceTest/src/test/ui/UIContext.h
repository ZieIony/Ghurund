#pragma once

#include "ui/UIContext.h"

namespace Ghurund::Core {
    class ResourceManager;
    class Window;
}

namespace UnitTest {
    class UiContext:public Ghurund::UI::IUIContext {
    public:
        UiContext(
            Ghurund::Core::Window& window,
            Ghurund::Core::ResourceManager& manager
        ):IUIContext(window, manager) {}
    };
}
