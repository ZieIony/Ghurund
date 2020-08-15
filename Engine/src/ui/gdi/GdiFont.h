#pragma once

#include "Common.h"
#include "core/string/String.h"
#include "core/Pointer.h"

#include <algorithm>
#include <objidl.h>
#include <gdiplus.h>

namespace Ghurund::UI {
    class Canvas;

    class Font :public Pointer {
    private:
        static inline const float MAX_SIZE = 32768.0f;

        struct Glyph {
            Gdiplus::RectF tightRect, fullRect;
        };

        Gdiplus::FontStyle style = Gdiplus::FontStyleRegular;
        float size;
        String familyName;
        bool italic = false;
        unsigned int weight = 400;
        Map<tchar, Glyph> glyphs;
        Gdiplus::Image* atlas;

    public:
        Gdiplus::Font* font;
        Gdiplus::FontFamily* fontFamily;

        Font(const String& family, float size);

        ~Font() {
            delete font;
            delete fontFamily;
        }

        float getAscent() {
            float em = fontFamily->GetEmHeight(style);
            return fontFamily->GetCellAscent(style) / em * size;
        }

        float getDescent() {
            float em = fontFamily->GetEmHeight(style);
            return fontFamily->GetCellDescent(style) / em * size;
        }

        float getLineHeight() {
            float em = fontFamily->GetEmHeight(style);
            return fontFamily->GetLineSpacing(style) / em * size;
        }

        void measureText(const String& text, float width, Gdiplus::SizeF* outSize) const;

        Gdiplus::Image* makeAtlas(const tchar* characters);

        void drawText(const String& text, float x, float y, Canvas& canvas) const;
    };
}