#include "GdiFont.h"
#include "ui/Canvas.h"

#include <commdlg.h>

namespace Ghurund::UI {
    Font::Font(const String& family, float size) {
        if (sizeof(tchar) == sizeof(char)) {
            fontFamily = new Gdiplus::FontFamily(UnicodeString(family));
        } else {
            fontFamily = new Gdiplus::FontFamily((UnicodeString&)family);
        }
        font = new Gdiplus::Font(fontFamily, size, style, Gdiplus::UnitPixel);

        this->size = size;
        this->familyName = family;
    }

    void Font::measureText(const String& text, float width, Gdiplus::SizeF* outSize) const {
        HDC hdcimage = CreateCompatibleDC(NULL);
        Gdiplus::Graphics graphics(hdcimage);
        graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
        graphics.SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintAntiAlias);
        Gdiplus::RectF rect(0, 0, width, MAX_SIZE);
        Gdiplus::RectF outRect;

        Gdiplus::StringFormat format;
        format.SetFormatFlags(Gdiplus::StringFormatFlagsNoFitBlackBox);
        format.SetTrimming(Gdiplus::StringTrimming::StringTrimmingCharacter);

        if (sizeof(tchar) == sizeof(char)) {
            graphics.MeasureString(UnicodeString(text), -1, font, rect, &format, &outRect);
        } else {
            graphics.MeasureString((UnicodeString&)text, -1, font, rect, &format, &outRect);
        }

        outSize->Width = outRect.GetRight();
        outSize->Height = outRect.GetBottom();
    }

    Gdiplus::Image* Font::makeAtlas(const tchar* characters) {
        HFONT hf;

        unsigned int atlasWidth = 1024, atlasHeight = 512;

        HDC hdcScreen = GetDC(NULL);
        HDC hdcBmp = CreateCompatibleDC(hdcScreen);
        HBITMAP bmp = CreateCompatibleBitmap(hdcScreen, atlasWidth, atlasHeight);
        HBITMAP hbmPrev = static_cast<HBITMAP>(SelectObject(hdcBmp, bmp));

        float lfHeight = -size * GetDeviceCaps(hdcScreen, LOGPIXELSY) / 72.0f;
        hf = CreateFont(lfHeight, 0, 0, 0, weight, italic ? TRUE : FALSE, 0, 0, 0, 0, 0, 0, 0, familyName.getData());
        SelectObject(hdcBmp, hf);
        TEXTMETRIC tm;
        GetTextMetrics(hdcBmp, &tm);

        RECT r = { 0, 0, (LONG)atlasWidth, (LONG)atlasHeight };
        FillRect(hdcBmp, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));

        HBRUSH rectBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
        SelectObject(hdcBmp, GetStockObject(BLACK_BRUSH));
        RECT rect;
        SetBkMode(hdcBmp, TRANSPARENT);

        unsigned int padding = size;
        SIZE charsSize;
        GetTextExtentPoint32(hdcBmp, characters, _tcslen(characters), &charsSize);

        unsigned int x = padding, y = padding;
        for (size_t i = 0; i <= strlen(characters); i++) {
            char c = characters[i];
            SIZE charSize;
            GetTextExtentPoint32A(hdcBmp, &c, 1, &charSize);
            if (x + charSize.cx >= atlasWidth) {
                x = padding;
                y += size + padding;
            }

            TextOut(hdcBmp, x, y, &c, 1);
            rect.left = x;
            rect.top = y + tm.tmExternalLeading + tm.tmInternalLeading;
            rect.right = x + charSize.cx;
            rect.bottom = y + tm.tmAscent + tm.tmDescent;
            glyphs.set(c, {
                Gdiplus::RectF(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top),
                Gdiplus::RectF(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top),
                });
            //FrameRect(hdcBmp, &rect, rectBrush);
            x += charSize.cx + padding;
        }

        SelectObject(hdcBmp, hbmPrev);
        DeleteDC(hdcBmp);
        ReleaseDC(NULL, hdcScreen);

        HPALETTE hpal = {};
        atlas = new Gdiplus::Bitmap(bmp, hpal);
        return atlas;
    }

    void Font::drawText(const String& text, float x, float y, Canvas& canvas) const {
        float currentX = x;
        for (size_t i = 0; i < text.Length; i++) {
            if (!glyphs.contains(text.get(i)))
                continue;

            Glyph& glyph = glyphs.get(text.get(i));
            canvas.drawImage(*atlas, currentX, y, glyph.tightRect);
            currentX += glyph.tightRect.Width;
        }
    }
}