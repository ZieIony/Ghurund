#pragma once

#include <Windows.h>

namespace Ghurund::Core {
    struct WindowMessage {
        unsigned int code;
        WPARAM wParam;
        uint64_t time;
        POINT mousePos;
    };
}
