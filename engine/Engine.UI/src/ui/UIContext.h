#pragma once

#include <dwrite.h>

namespace Ghurund {
    class Window;
}

namespace Ghurund::UI {
    class LayoutLoader;

    class UIContext {
    private:
        IDWriteFactory& dwriteFactory;
        Ghurund::Window& window;
        LayoutLoader& loader;

    public:
        UIContext(IDWriteFactory& dwriteFactory, Ghurund::Window& window, LayoutLoader& loader):
            dwriteFactory(dwriteFactory), window(window), loader(loader) {}

        inline IDWriteFactory& getDWriteFactory() {
            return dwriteFactory;
        }

        __declspec(property(get = getDWriteFactory)) IDWriteFactory& DWriteFactory;

        inline Ghurund::Window& getWindow() {
            return window;
        }

        __declspec(property(get = getWindow)) Ghurund::Window& Window;

        inline LayoutLoader& getLayoutLoader() {
            return loader;
        }

        __declspec(property(get = getLayoutLoader)) LayoutLoader& LayoutLoader;
    };
}