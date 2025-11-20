#pragma once

#include "ui/UIContext.h"

namespace Ghurund::Core {
    class ResourceManager;
    class Window;
}

namespace Ghurund::UI::OpenGL {
    using namespace Ghurund::Core;

    class OglUiContext:public IUIContext {
    public:
        OglUiContext(
            Ghurund::Core::Window& window
        ):IUIContext(window) {}
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::OpenGL::OglUiContext>();
}