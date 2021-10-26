#pragma once

namespace Ghurund::Core {

    enum class WindowAttributes {
        MINIMIZE_BUTTON = 1,
        MAXIMIZE_BUTTON = 2,
        TITLE = 4,
        RESIZE_BORDER = 8,
        THIN_BORDER = 16,
        SHOW_ON_TASKBAR = 32
    };

    WindowAttributes operator |(WindowAttributes lhs, WindowAttributes rhs);

    bool operator &(WindowAttributes lhs, WindowAttributes rhs);

}