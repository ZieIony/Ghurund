#pragma once

#include "core/reflection/Type.h"
#include "font/Font.h"

namespace Ghurund::Core {
    class ResourceManager;
    class Window;
}

namespace Ghurund::UI {
    class UIContext {
    private:
        Ghurund::Core::Window& window;

    public:
        UIContext(Ghurund::Core::Window& window):window(window) {}

        inline Ghurund::Core::Window& getWindow() {
            return window;
        }

        __declspec(property(get = getWindow)) Ghurund::Core::Window& Window;

        virtual Resource* makeControlMesh() = 0;

        virtual Resource* makeTextMesh(const WString& text, const Font& font) = 0;
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::UIContext>();
}