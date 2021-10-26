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
        void init() {
            Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
        }

        void uninit() {
            Gdiplus::GdiplusShutdown(gdiplusToken);
        }
    };
}