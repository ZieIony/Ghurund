#include "ghcpch.h"
#include "WindowClass.h"

#include "SystemWindow.h"
#include "core/input/Keyboard.h"
#include "core/input/Mouse.h"
#include "core/logging/Formatter.h"

#include <windowsx.h>

namespace Ghurund {
    const WindowClass WindowClass::WINDOWED = WindowClass(WindowClassEnum::WINDOWED, "WINDOWED", WS_EX_APPWINDOW, WS_OVERLAPPEDWINDOW, 0);
    const WindowClass WindowClass::FULLSCREEN = WindowClass(WindowClassEnum::FULLSCREEN, "FULLSCREEN", WS_EX_APPWINDOW, WS_POPUP | WS_EX_TOPMOST, 0);
    const WindowClass WindowClass::POPUP = WindowClass(WindowClassEnum::POPUP, "POPUP", WS_EX_NOACTIVATE, WS_POPUP, CS_DROPSHADOW);

    const EnumValues<WindowClassEnum, WindowClass> WindowClass::VALUES = {
        &WindowClass::WINDOWED,
        &WindowClass::FULLSCREEN,
        &WindowClass::POPUP
    };

    WindowClass::WindowClass(WindowClassEnum value, const AString& name, DWORD exStyle, DWORD dwStyle, UINT style):Enum<WindowClassEnum, WindowClass>(value, name) {
        this->exStyle = exStyle;
        this->dwStyle = dwStyle;
        className = std::format(_T("Ghurund{}"), name).c_str();

        hInst = GetModuleHandle(0);

        windowClass.cbSize = sizeof(WNDCLASSEX);
        windowClass.style = style;
        windowClass.lpfnWndProc = &windowProc;
        windowClass.cbClsExtra = 0L;
        windowClass.cbWndExtra = 0L;
        windowClass.hInstance = hInst;
        windowClass.hIcon = 0;
        windowClass.hCursor = nullptr;
        windowClass.hbrBackground = 0;
        windowClass.lpszMenuName = 0;
        windowClass.lpszClassName = className.Data;
        windowClass.hIconSm = 0;

        RegisterClassEx(&windowClass);
    }

    HWND WindowClass::create() const {
        return CreateWindowEx(exStyle, windowClass.lpszClassName, _T("Ghurund"), dwStyle, 0, 0, 0, 0, nullptr, nullptr, windowClass.hInstance, nullptr);
    }

}