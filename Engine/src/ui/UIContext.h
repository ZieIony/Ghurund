#pragma once

namespace Ghurund {
    class Window;
}

namespace Ghurund::UI {
    class Graphics2D;
    class LayoutLoader;

    class UIContext {
    private:
        Graphics2D& graphics;
        Ghurund::Window& window;
        LayoutLoader& loader;

    public:
        UIContext(Graphics2D& graphics, Ghurund::Window& window, LayoutLoader& loader):
            graphics(graphics), window(window), loader(loader) {}

        inline Graphics2D& getGraphics() {
            return graphics;
        }

        __declspec(property(get = getGraphics)) Graphics2D& Graphics;

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