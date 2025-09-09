#pragma once

#include <Windows.h>

namespace Ghurund::Core {
    struct WindowMessage {
        unsigned int code;
        WPARAM wParam;
        LPARAM lParam;
        uint64_t time;
    };
}
