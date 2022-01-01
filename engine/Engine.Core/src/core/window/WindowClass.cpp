#include "ghcpch.h"
#include "WindowClass.h"

#include "SystemWindow.h"
#include "core/input/Keyboard.h"
#include "core/input/Mouse.h"
#include "core/logging/Formatter.h"

#include <windowsx.h>

namespace Ghurund::Core {
    WindowClass::WindowClass(WindowStyle windowStyle, WNDPROC windowProc, const tchar* className) {
        exStyle = windowStyle.showOnTaskbar ? WS_EX_APPWINDOW : WS_EX_NOACTIVATE;
        dwStyle =
            (windowStyle.hasMinimizeButton ? WS_MINIMIZEBOX | WS_SYSMENU : 0) |
            (windowStyle.hasMaximizeButton ? WS_MAXIMIZEBOX | WS_SYSMENU : 0) |
            (windowStyle.hasTitle ? WS_CAPTION | WS_SYSMENU : 0) |
            (windowStyle.borderStyle == WindowBorderStyle::RESIZE ? WS_THICKFRAME : 0) |
            (windowStyle.borderStyle == WindowBorderStyle::THIN ? WS_BORDER : 0);

        if (className) {
            this->className = className;
        } else {
            this->className = std::format(_T("Ghurund{}{}{}{}{}{}"),
                windowStyle.hasMaximizeButton ? 1 : 0,
                windowStyle.hasMinimizeButton ? 1 : 0,
                windowStyle.hasTitle ? 1 : 0,
                (size_t)windowStyle.borderStyle,
                windowStyle.showOnTaskbar ? 1 : 0,
                windowStyle.hasShadow ? 1 : 0
            ).c_str();
        }

        UINT style = windowStyle.hasShadow ? CS_DROPSHADOW : 0;

        HINSTANCE hInst = GetModuleHandle(0);

        windowClass = {
            .cbSize = sizeof(WNDCLASSEX),
            .style = style,
            .lpfnWndProc = windowProc,
            .cbClsExtra = 0L,
            .cbWndExtra = 0L,
            .hInstance = hInst,
            .hIcon = 0,
            .hCursor = nullptr,
            .hbrBackground = 0,
            .lpszMenuName = 0,
            .lpszClassName = this->className.Data,
            .hIconSm = 0
        };

        RegisterClassEx(&windowClass);
    }

    HWND WindowClass::create() const {
        return CreateWindowEx(exStyle, windowClass.lpszClassName, nullptr, dwStyle, 0, 0, 0, 0, nullptr, nullptr, windowClass.hInstance, nullptr);
    }

}