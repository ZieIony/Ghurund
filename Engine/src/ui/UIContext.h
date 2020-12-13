#pragma once

namespace Ghurund::UI {
    class Graphics2D;
    class Theme;
    class Window;

    class UIContext {
    private:
        Graphics2D& graphics;
        Theme& theme;
        Ghurund::Window& window;

    public:
        UIContext(Graphics2D& graphics, Theme& theme, Ghurund::Window& window):
            graphics(graphics), theme(theme), window(window) {}

        inline Graphics2D& getGraphics() {
            return graphics;
        }

        __declspec(property(get = getGraphics)) Graphics2D& Graphics;

        inline Theme& getTheme() {
            return theme;
        }

        __declspec(property(get = getTheme)) Theme& Theme;

        inline Ghurund::Window& getWindow() {
            return window;
        }

        __declspec(property(get = getWindow)) Ghurund::Window& Window;
    };
}