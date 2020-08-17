#include "GdiFont.h"
#include "ui/Canvas.h"

#include <commdlg.h>

namespace Ghurund::UI {
    Font::Font(const String& family, float size, unsigned int weight, bool italic, const tchar* supportedCharacters) {
        this->size = size;
        this->familyName = family;
        this->weight = weight;
        this->italic = italic;
        makeAtlas(supportedCharacters ? supportedCharacters : DEFAULT_CHARACTER_SET);
    }

    void Font::measureText(const String& text, float width, Gdiplus::SizeF* outSize) const {
        float measuredWidth = 0;
        for (size_t i = 0; i < text.Length; i++) {
            if (!glyphs.contains(text.get(i)))
                continue;

            Glyph& glyph = glyphs.get(text.get(i));
            measuredWidth += glyph.tightRect.Width;
        }

        outSize->Width = measuredWidth;
        outSize->Height = getAscent() + getDescent();
    }

    void Font::makeAtlas(const tchar* characters) {
        HFONT hf;

        unsigned int atlasWidth = 1024, atlasHeight = 512;

        HDC hdcScreen = GetDC(NULL);
        HDC hdcBmp = CreateCompatibleDC(hdcScreen);
        SetBkMode(hdcScreen, TRANSPARENT);

        BITMAPINFO bmi;
        int32_t* pixels = nullptr;
        HBITMAP bmp = makeDIB(hdcScreen, bmi, atlasWidth, atlasHeight, &pixels);
        HBITMAP hbmPrev = static_cast<HBITMAP>(SelectObject(hdcBmp, bmp));

        float lfHeight = -size * GetDeviceCaps(hdcScreen, LOGPIXELSY) / 72.0f;
        hf = CreateFont(lfHeight, 0, 0, 0, weight, italic ? TRUE : FALSE, 0, 0, 0, 0, 0, 0, 0, familyName.getData());
        SelectObject(hdcBmp, hf);

        GetTextMetrics(hdcBmp, &tm);

        initKerning(hdcBmp);

        initGlyphs(hdcBmp, characters, atlasWidth);

        SelectObject(hdcBmp, hbmPrev);
        DeleteDC(hdcBmp);
        ReleaseDC(NULL, hdcScreen);

        makeAtlasBitmap(atlasWidth, atlasHeight, pixels);
    }

    void Font::initGlyphs(HDC context, const tchar* characters, unsigned int width) {
        //HBRUSH rectBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
        RECT rect;
        SetBkMode(context, TRANSPARENT);
        SetTextColor(context, 0xffffff);

        unsigned int padding = (unsigned int)size;
        /*SIZE charsSize;   // TODO: measure atlas size
        GetTextExtentPoint32(hdcBmp, characters, _tcslen(characters), &charsSize);*/

        unsigned int x = padding, y = padding;
        for (size_t i = 0; i < strlen(characters); i++) {
            char c = characters[i];
            SIZE charSize;
            GetTextExtentPoint32(context, &c, 1, &charSize);
            if (x + charSize.cx >= width) {
                x = padding;
                y += size + padding;
            }

            TextOut(context, x, y, &c, 1);
            rect.left = x;
            rect.top = y + tm.tmExternalLeading + tm.tmInternalLeading;
            rect.right = x + charSize.cx;
            rect.bottom = y + tm.tmAscent + tm.tmDescent;
            Glyph glyph = {
                Gdiplus::RectF((float)rect.left, (float)rect.top, (float)(rect.right - rect.left), (float)(rect.bottom - rect.top)),
                Gdiplus::RectF(
                    (float)(rect.left - padding / 2),
                    (float)(rect.top - tm.tmExternalLeading - tm.tmInternalLeading),
                    (float)(rect.right - rect.left + padding),
                    (float)(rect.bottom - rect.top + tm.tmExternalLeading + tm.tmInternalLeading)
                )
            };
            glyphs.set(c, glyph);
            //FrameRect(hdcBmp, &rect, rectBrush);
            x += charSize.cx + padding;
        }

        // DeleteObject(rectBrush);
    }

    void Font::makeAtlasBitmap(unsigned int width, unsigned int height, int32_t* pixels) {
        atlas = new Gdiplus::Bitmap(width, height, width * 4, PixelFormat32bppARGB, (BYTE*)pixels);
        atlas->RotateFlip(Gdiplus::RotateNoneFlipY);
        Gdiplus::Color pixel;
        for (unsigned int x = 0; x < width; x++) {
            for (unsigned int y = 0; y < height; y++) {
                atlas->GetPixel(x, y, &pixel);
                pixel.SetValue((pixel.GetValue() & 0xff) << 24);
                atlas->SetPixel(x, y, pixel);
            }
        }
    }

    HBITMAP Font::makeDIB(HDC context, BITMAPINFO& bmi, unsigned int width, unsigned int height, int32_t** pixels) {
        ZeroMemory(&bmi, sizeof(BITMAPINFO));
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = width;
        bmi.bmiHeader.biHeight = height;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biSizeImage = bmi.bmiHeader.biWidth * bmi.bmiHeader.biHeight * 4;

        return CreateDIBSection(context, &bmi, DIB_RGB_COLORS, (void**)pixels, NULL, 0x0);
    }

    void Font::drawText(Canvas& canvas, const String& text, float x, float y, int32_t color) const {
        float currentX = x;
        for (size_t i = 0; i < text.Length; i++) {
            tchar c = text.get(i);
            if (!glyphs.contains(c))
                continue;

            Glyph& glyph = glyphs.get(c);
            canvas.drawImage(*atlas, currentX + (glyph.fullRect.X - glyph.tightRect.X), y, glyph.fullRect, color);

            if (i < text.Length - 1) {
                for (unsigned int j = 0; j < kerningPairCount; j++) {
                    tchar c2 = text.get(i + 1);
                    KERNINGPAIR pair = kerningPairs[j];
                    if (pair.wFirst == c && pair.wSecond == c2) {
                        currentX += pair.iKernAmount;
                        break;
                    }
                }
            }
            currentX += glyph.tightRect.Width;
        }
    }
}