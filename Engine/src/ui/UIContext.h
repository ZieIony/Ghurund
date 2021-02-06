#pragma once

namespace Ghurund::UI {
    class Graphics2D;
    class Window;

    class UIContext {
    private:
        Graphics2D& graphics;
        Ghurund::Window& window;

    public:
        UIContext(Graphics2D& graphics, Ghurund::Window& window):
            graphics(graphics), window(window) {}

        inline Graphics2D& getGraphics() {
            return graphics;
        }

        __declspec(property(get = getGraphics)) Graphics2D& Graphics;

        inline Ghurund::Window& getWindow() {
            return window;
        }

        __declspec(property(get = getWindow)) Ghurund::Window& Window;
    };
}