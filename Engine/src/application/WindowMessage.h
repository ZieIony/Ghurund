#pragma once

#include <Windows.h>

namespace Ghurund {
    struct WindowMessage {
        unsigned int code;
        WPARAM wParam;
        uint64_t time;
        POINT mousePos;
    };
}
