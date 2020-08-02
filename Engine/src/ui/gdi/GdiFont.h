#pragma once

#include "ui/Font.h"

namespace Ghurund {
    class GdiFont :public Font {
    private:
        static inline const float MAX_SIZE = 32768.0f;

    public:
        Gdiplus::Font* font;
        Gdiplus::FontFamily* fontFamily;

        GdiFont(const String& family, float size) {
            if (sizeof(tchar) == sizeof(char)) {
                fontFamily = new Gdiplus::FontFamily(UnicodeString(family));
            } else {
                fontFamily = new Gdiplus::FontFamily((UnicodeString&)family);
            }
            font = new Gdiplus::Font(fontFamily, size, Gdiplus::FontStyleRegular, Gdiplus::UnitPoint);
        }

        ~GdiFont() {
            delete font;
            delete fontFamily;
        }

        virtual void measureText(const String& text, float width, Gdiplus::SizeF* outSize) const override;
    };
}