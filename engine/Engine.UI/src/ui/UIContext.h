#pragma once

#include <dwrite.h>

namespace Ghurund::Core {
    class ResourceManager;
    class Window;
}

namespace Ghurund::UI {
    class UIContext {
    private:
        IDWriteFactory& dwriteFactory;
        Ghurund::Core::Window& window;
        Ghurund::Core::ResourceManager& manager;

    public:
        UIContext(IDWriteFactory& dwriteFactory, Ghurund::Core::Window& window, Ghurund::Core::ResourceManager& manager):
            dwriteFactory(dwriteFactory), window(window), manager(manager) {}

        inline IDWriteFactory& getDWriteFactory() {
            return dwriteFactory;
        }

        __declspec(property(get = getDWriteFactory)) IDWriteFactory& DWriteFactory;

        inline Ghurund::Core::Window& getWindow() {
            return window;
        }

        __declspec(property(get = getWindow)) Ghurund::Core::Window& Window;

        inline Ghurund::Core::ResourceManager& getResourceManager() {
            return manager;
        }

        __declspec(property(get = getResourceManager)) Ghurund::Core::ResourceManager& ResourceManager;
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::UIContext>();
}