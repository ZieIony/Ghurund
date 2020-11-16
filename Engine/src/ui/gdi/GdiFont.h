#pragma once

#include "Gdi.h"
#include "Common.h"
#include "core/string/String.h"
#include "core/ScopedPointer.h"

namespace Ghurund::UI {
    class Canvas;
    class Control;

    class TextSelection {
    public:
        Control* control;
        size_t index = 0;
        float x;
    };

    class Font:public Pointer {
    private:
        static inline const tchar* DEFAULT_CHARACTER_SET = _T("aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPrqQRsStTuUvVwWxXyYzZ 0123456789/*-+[]{};':\",./<>?!@#$%^&*()`~Û”øØüèÒ—Ê∆úåπ•Í ");

        struct Glyph {
            Gdiplus::RectF tightRect, fullRect;
        };

        float size;
        String familyName;
        bool italic = false;
        unsigned int weight = 400;

        TEXTMETRIC tm;

        Map<tchar, Glyph> glyphs;
        unsigned int kerningPairCount;
        KERNINGPAIR* kerningPairs;

        Gdiplus::Image* atlas = nullptr;

        void makeAtlas(const tchar* characters);

        inline void initKerning(HDC context) {
            kerningPairCount = GetKerningPairs(context, 0, nullptr);
            kerningPairs = ghnew KERNINGPAIR[kerningPairCount];
            GetKerningPairs(context, kerningPairCount, kerningPairs);
        }

        void initGlyphs(HDC context, const tchar* characters, unsigned int width);

        void makeAtlasBitmap(unsigned int width, unsigned int height, int32_t* pixels);

        HBITMAP makeDIB(HDC context, BITMAPINFO& bmi, unsigned int width, unsigned int height, int32_t** pixels);

    public:
        Font(const String& family, float size, unsigned int weight = 400, bool italic = false, const tchar* supportedCharacters = nullptr);

        Font(const String& fileName, const String& family, float size, unsigned int weight = 400, bool italic = false, const tchar* supportedCharacters = nullptr);

        ~Font() {
            delete kerningPairs;
            if (atlas)
                delete atlas;
        }

        long getAscent() const {
            return tm.tmAscent;
        }

        long getDescent() const {
            return tm.tmDescent;
        }

        long getInternalLeading() const {
            return tm.tmInternalLeading;
        }

        long getExternalLeading() const {
            return tm.tmExternalLeading;
        }

        long getHeight() const {
            return tm.tmHeight;
        }

        void measureText(const String& text, float width, Gdiplus::SizeF* outSize) const;

        void drawText(Canvas& canvas, const String& text, float x, float y, int32_t color) const;

        TextSelection findSelection(const String& text, float x) const;
    };
}