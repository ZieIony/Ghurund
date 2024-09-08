#pragma once

#include "Window.h"

namespace Ghurund::Core {
    class SystemWindow;

    struct WindowData {
        SystemWindow* window;
        bool mouseTracked = false;

        WindowData(SystemWindow* w):window(w) {}
    };

    LRESULT CALLBACK windowProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);
}