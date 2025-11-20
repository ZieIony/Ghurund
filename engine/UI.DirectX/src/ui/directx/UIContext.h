#pragma once

#include "ui/UIContext.h"

namespace Ghurund::Core {
    class ResourceManager;
    class Window;
}

namespace Ghurund::UI::DirectX {
    using namespace Ghurund::Core;

    class UiContext:public IUIContext {
    public:
        UiContext(
            Ghurund::Core::Window& window
        ):IUIContext(window) {}
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::DirectX::UiContext>();
}