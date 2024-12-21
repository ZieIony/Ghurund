#pragma once

#include <Windows.h>

namespace Ghurund::Core {
    LRESULT CALLBACK windowProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);
}