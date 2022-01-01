#pragma once

#include "core/Object.h"
#include "core/string/String.h"
#include "core/window/WindowStyle.h"
#include "core/window/WindowProc.h"

namespace Ghurund::Core {
    class WindowClass {
    private:
        String className;
        WNDCLASSEX windowClass;
        DWORD exStyle, dwStyle;

        WindowClass(const WindowClass& other) = delete;

    public:
        WindowClass(WindowStyle style, WNDPROC windowProc = &windowProc, const tchar* className = nullptr);

        ~WindowClass(){
            UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
        }

        HWND create() const;

        inline DWORD getStyle() const {
            return dwStyle;
        }

        __declspec(property(get = getStyle)) DWORD Style;
    };
}