#include "ghcpch.h"
#include "WindowStyle.h"

namespace Ghurund::Core {
    const WindowStyle& WindowStyle::FULLSCREEN = WindowStyle{
        .hasMinimizeButton = false,
        .hasMaximizeButton = false,
        .hasTitle = false,
        .borderStyle = WindowBorderStyle::NONE,
        .showOnTaskbar = true,
        .hasShadow = false
    };
}