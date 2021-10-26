#include "ghcpch.h"
#include "WindowAttributes.h"

namespace Ghurund::Core {
    WindowAttributes operator|(WindowAttributes lhs, WindowAttributes rhs) {
        return (WindowAttributes)((std::underlying_type<WindowAttributes>::type)lhs | (std::underlying_type<WindowAttributes>::type)rhs);
    }

    bool operator&(WindowAttributes lhs, WindowAttributes rhs) {
        return (std::underlying_type<WindowAttributes>::type)lhs & (std::underlying_type<WindowAttributes>::type)rhs;
    }
}
