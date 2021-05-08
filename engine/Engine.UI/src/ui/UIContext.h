#pragma once

#include <dwrite.h>

namespace Ghurund {
    class ResourceManager;
    class Window;
}

namespace Ghurund::UI {
    class LayoutLoader;

    class UIContext {
    private:
        IDWriteFactory& dwriteFactory;
        Ghurund::Window& window;
        ResourceManager& manager;

    public:
        UIContext(IDWriteFactory& dwriteFactory, Ghurund::Window& window, ResourceManager& manager):
            dwriteFactory(dwriteFactory), window(window), manager(manager) {}

        inline IDWriteFactory& getDWriteFactory() {
            return dwriteFactory;
        }

        __declspec(property(get = getDWriteFactory)) IDWriteFactory& DWriteFactory;

        inline Ghurund::Window& getWindow() {
            return window;
        }

        __declspec(property(get = getWindow)) Ghurund::Window& Window;

        inline ResourceManager& getResourceManager() {
            return manager;
        }

        __declspec(property(get = getResourceManager)) ResourceManager& ResourceManager;
    };
}