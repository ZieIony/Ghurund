#pragma once

#include "core/Enum.h"
#include "core/Event.h"
#include "core/NamedObject.h"
#include "core/Object.h"
#include "core/string/String.h"

namespace Ghurund {
    class Window;

    enum class WindowClassEnum {
        WINDOWED, FULLSCREEN, POPUP
    };

    class WindowClass:public Enum<WindowClassEnum, WindowClass> {
    private:
        String className;
        WNDCLASSEX windowClass;
        HINSTANCE hInst;
        DWORD exStyle, dwStyle;

    public:
        static const WindowClass WINDOWED, FULLSCREEN, POPUP;

        static const EnumValues<WindowClassEnum, WindowClass> VALUES;

        WindowClass(WindowClassEnum value, const tchar* name, DWORD exStyle, DWORD dwStyle, UINT style);

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