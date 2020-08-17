#pragma once

#define GDIPVER     0x0110

namespace Gdiplus {
    class Graphics;
}

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
        Gdiplus::Bitmap* atlas;

        Font(const String& family, float size, unsigned int weight = 400, bool italic = false, const tchar* supportedCharacters = nullptr);

        ~Font() {
            delete kerningPairs;
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
    };
}