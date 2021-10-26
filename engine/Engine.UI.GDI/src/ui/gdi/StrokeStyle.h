#pragma once

#include "core/collection/Array.h"
#include "ui/StrokeStyle.h"

#undef GDIPVER
#define GDIPVER     0x0110

#include <gdiplus.h>

namespace Ghurund::UI::GDI {
    using namespace Ghurund::Core;

    class StrokeStyle:public IStrokeStyle {
    private:
        Gdiplus::DashStyle dashStyle;

    public:
        void init(Gdiplus::DashStyle dashStyle) {
            this->dashStyle = dashStyle;
        }

        inline Gdiplus::DashStyle get() {
            return dashStyle;
        }
    };
}