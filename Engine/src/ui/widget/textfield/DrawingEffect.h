#pragma once

#include "IUnknownImpl.h"

namespace Ghurund::UI {
    class DECLSPEC_UUID("1CD7C44F-526B-492a-B780-EF9C4159B653") DrawingEffect: public ComBase<QiList<IUnknown> > {
    private:
        uint32_t color;

    public:
        DrawingEffect(uint32_t color): color(color) {}

        inline uint32_t getColor() const throw() {
            return color;
        }

        inline COLORREF getColorRef() const throw() {
            return getColorRef(color);
        }

        static inline COLORREF getColorRef(uint32_t bgra) throw() {
            return RGB(GetBValue(bgra), GetGValue(bgra), GetRValue(bgra));
        }

        static inline COLORREF getBgra(COLORREF rgb) throw() {
            return RGB(GetBValue(rgb), GetGValue(rgb), GetRValue(rgb)) | 0xFF000000;
        }
    };
}