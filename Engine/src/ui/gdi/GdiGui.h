#pragma once

#include "ui/Gui.h"
#include "GdiCanvas.h"

#pragma comment (lib, "Gdiplus.lib")

namespace Ghurund::UI {
    class GdiGui :public Gui {
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

        Canvas* makeCanvas(HWND handle) {
            return ghnew GdiCanvas(handle);
        }
    };
}