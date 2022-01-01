#pragma once

namespace Ghurund::Core {
    enum class WindowBorderStyle {
        RESIZE, THIN, NONE
    };

    struct WindowStyle {
        bool hasMinimizeButton = false;
        bool hasMaximizeButton = false;
        bool hasTitle = false;
        WindowBorderStyle borderStyle = WindowBorderStyle::NONE;
        bool showOnTaskbar = false;
        bool hasShadow = false;

        auto operator<=>(const WindowStyle& other) const = default;
    };
}