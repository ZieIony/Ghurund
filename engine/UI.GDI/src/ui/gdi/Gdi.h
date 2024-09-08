#pragma once

#undef GDIPVER
#define GDIPVER     0x0110

#include <objidl.h>
#include <gdiplus.h>

#pragma comment (lib, "Gdiplus.lib")

namespace Ghurund::UI::GDI {
    class Gdi {
    private:
        Gdiplus::GdiplusStartupInput gdiplusStartupInput;
        ULONG_PTR gdiplusToken;

    public:
        Gdi() {
            Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
        }

        ~Gdi() {
            Gdiplus::GdiplusShutdown(gdiplusToken);
        }
    };
}