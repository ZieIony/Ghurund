#include "ghuipch.h"
#include "Font.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"

#include "core/image/Image.h"
#include "core/image/ImageLoader.h"
#include "core/math/Bezier.h"
#include "ui/Color.h"
#include "Ttf.h"

#include <msdfgen.h>

namespace Ghurund::UI {

    inline msdfgen::Point2 fromFixed(POINTFX& p) {
        return {
            p.x.value + p.x.fract / (double)0x10000,
            p.y.value + p.y.fract / (double)0x10000
        };
    }

    inline byte pixelFloatToByte(float value) {
        return (byte)std::max(0.0f, std::min(255.0f * value, 255.0f));
    }

    msdfgen::Shape shapeFromPolygonData(byte* data, DWORD size, GLYPHMETRICS& glyphMetrics, IntSize glyphSize, uint32_t padding) {
        auto tx = [&](float x) {
            float offset = (std::max(glyphMetrics.gmBlackBoxX, glyphMetrics.gmBlackBoxY) - glyphMetrics.gmBlackBoxX) / 2.0f;
            return (x - glyphMetrics.gmptGlyphOrigin.x + offset) / std::max(glyphMetrics.gmBlackBoxX, glyphMetrics.gmBlackBoxY) * (glyphSize.Width - padding * 2) + padding;
        };
        auto ty = [&](float y) {
            float offset = (std::max(glyphMetrics.gmBlackBoxX, glyphMetrics.gmBlackBoxY) - glyphMetrics.gmBlackBoxY) / 2.0f;
            return (glyphMetrics.gmptGlyphOrigin.y - y - offset) / std::max(glyphMetrics.gmBlackBoxX, glyphMetrics.gmBlackBoxY) * (glyphSize.Height - padding * 2) + padding;
        };

        msdfgen::Shape shape;
        while (size > 0) {
            TTPOLYGONHEADER header = *(TTPOLYGONHEADER*)data;
            data += sizeof(TTPOLYGONHEADER);
            size_t polygonSize = header.cb - sizeof(TTPOLYGONHEADER);
            msdfgen::Point2 start = fromFixed(header.pfxStart);
            msdfgen::Point2 current = start;

            // read primitives of this polygon
            msdfgen::Contour contour;
            while (polygonSize > 0) {
                List<BezierCubic> beziers;
                TTPOLYCURVE* curve = (TTPOLYCURVE*)data;
                if (curve->wType == TT_PRIM_LINE) {
                    for (size_t j = 0; j < curve->cpfx; j++) {
                        msdfgen::Point2 p2 = fromFixed(curve->apfx[j]);
                        contour.addEdge(new msdfgen::LinearSegment({ tx(current.x),ty(current.y) }, { tx(p2.x),ty(p2.y) }));
                        current = p2;
                    }
                } else if (curve->wType == TT_PRIM_QSPLINE) {
                    for (size_t j = 0; j < curve->cpfx - 1; j++) {
                        msdfgen::Point2 p2 = fromFixed(curve->apfx[j]);
                        msdfgen::Point2 p3 = fromFixed(curve->apfx[j + 1]);
                        if (j < curve->cpfx - 2) {
                            p3.x = (p2.x + p3.x) / 2;
                            p3.y = (p2.y + p3.y) / 2;
                        } else {
                            p3 = fromFixed(curve->apfx[j + 1]);
                        }
                        contour.addEdge(new msdfgen::QuadraticSegment({ tx(current.x),ty(current.y) }, { tx(p2.x),ty(p2.y) }, { tx(p3.x),ty(p3.y) }));
                        current = p3;
                    }
                } else if (curve->wType == TT_PRIM_CSPLINE) {
                    /*for (size_t j = 0; j < curve->cpfx - 2; j += 3) {
                        msdfgen::Point2 p2 = fromFixed(curve->apfx[j]);
                        msdfgen::Point2 p3 = fromFixed(curve->apfx[j + 1]);
                        msdfgen::Point2 p4 = fromFixed(curve->apfx[j + 2]);
                        contour.addEdge(new msdfgen::CubicSegment(current, p2, p3, p4));
                        current = p4;
                    }*/
                }
                size_t curveSize = (sizeof(WORD) * 2 + curve->cpfx * sizeof(POINTFX));
                data += curveSize;
                polygonSize -= curveSize;
            }
            if (start != current)
                contour.addEdge(new msdfgen::LinearSegment({ tx(current.x),ty(current.y) }, { tx(start.x),ty(start.y) }));
            shape.addContour(contour);
            size -= header.cb;
        }

        return shape;
    }

    const Ghurund::Core::Type& Font::GET_TYPE() {
        static auto PROPERTY_FAMILYNAME = Property<Font, const WString&>("FamilyName", &getFamilyName);

        static const auto CONSTRUCTOR = Constructor<Font>();

        static const Ghurund::Core::Type TYPE = TypeBuilder<Font>(Ghurund::UI::NAMESPACE_NAME, "Font")
            .withProperty(PROPERTY_FAMILYNAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void Font::initAtlas(const String& supportedCharacters) {
        HDC hdcScreen = GetDC(NULL);

        float size = 12.0f;
        float lfHeight = -size * GetDeviceCaps(hdcScreen, LOGPIXELSY) / 72.0f;
        HFONT hf = CreateFont(lfHeight, 0, 0, 0, weight, italic ? TRUE : FALSE, 0, 0, 0, 0, 0, CLEARTYPE_QUALITY, 0, familyName.getData());

        initKerning(hf);

        initMsdf(hf, supportedCharacters);

        ReleaseDC(NULL, hdcScreen);
    }

    void Font::init(const void* data, size_t size, const String& supportedCharacters) {
        TtfFile file = {};
        file.init(data, size);
        familyName = file.readFontName();
        weight = file.readFontWeight();
        italic = file.readFontItalic();
        DWORD numFonts = {};
        uninit();
        handle = AddFontMemResourceEx((void*)data, size, 0, &numFonts);
        init(supportedCharacters);
    }

    void Font::uninit() {
        if (atlas) {
            atlas->release();
            atlas = nullptr;
        }
        glyphs.clear();
        kerning.clear();
        if (handle != INVALID_HANDLE_VALUE) {
            RemoveFontMemResourceEx(handle);
            handle = INVALID_HANDLE_VALUE;
        }
    }

    void Font::initKerning(HFONT hf) {
        HDC hdcScreen = GetDC(NULL);
        HDC hdcBmp = CreateCompatibleDC(hdcScreen);
        SelectObject(hdcBmp, hf);

        kerning.clear();
        unsigned int kerningPairCount = GetKerningPairs(hdcBmp, 0, nullptr);
        KERNINGPAIR* kerningPairs = ghnew KERNINGPAIR[kerningPairCount];
        GetKerningPairs(hdcBmp, kerningPairCount, kerningPairs);
        for (size_t i = 0; i < kerningPairCount; i++) {
            size_t index = kerning.indexOfKey(kerningPairs[i].wFirst);
            if (index == kerning.Size) {
                Map<tchar, int> map;
                map.set(kerningPairs[i].wSecond, kerningPairs[i].iKernAmount);
                kerning.set(kerningPairs[i].wFirst, map);
            } else {
                kerning.getValue(index).set(kerningPairs[i].wSecond, kerningPairs[i].iKernAmount);
            }
        }
        delete[] kerningPairs;
        DeleteDC(hdcBmp);
        ReleaseDC(NULL, hdcScreen);
    }

    void Font::initMsdf(HFONT hf, const String& characters) {
        HDC hdcScreen = GetDC(NULL);
        HDC hdcBmp = CreateCompatibleDC(hdcScreen);
        SelectObject(hdcBmp, hf);

        IntSize glyphSize = { 128, 128 };
        uint32_t charactersPerRow = std::bit_ceil((uint32_t)std::ceilf(std::log2f(characters.Length)));
        uint32_t atlasWidth = charactersPerRow * glyphSize.Width;
        IntSize atlasSize = { atlasWidth, atlasWidth };
        uint32_t pixelSize = ImageLoader::getDXGIFormatBitsPerPixel(DXGI_FORMAT_R8G8B8A8_UNORM) / 8;
        uint32_t rowPitch = pixelSize * atlasSize.Width;
        Buffer atlasData(rowPitch * atlasSize.Height);
        if (atlas)
            atlas->release();
        atlas = ghnew Image();

        GLYPHMETRICS glyphMetrics;
        glyphs.clear();
        MAT2 mat = { {0, 1}, {0, 0}, {0, 0}, {0, 1} };
        uint32_t maxDist = 8, padding = 2;
        for (size_t i = 0; i < characters.Length; i++) {
            tchar c = characters[i];
            uint32_t column = i % charactersPerRow;
            uint32_t row = i / charactersPerRow;

            DWORD result = GetGlyphOutline(hdcBmp, c, GGO_NATIVE, &glyphMetrics, 0, nullptr, &mat);
            if (result == GDI_ERROR)
                break;
            DWORD size = result;
            byte* data = ghnew byte[size];
            result = GetGlyphOutline(hdcBmp, c, GGO_NATIVE, &glyphMetrics, size, data, &mat);
            if (result == GDI_ERROR)
                break;

            msdfgen::Shape shape = shapeFromPolygonData(data, size, glyphMetrics, glyphSize, maxDist + padding);

            shape.normalize();
            msdfgen::edgeColoringByDistance(shape, 3);
            msdfgen::Bitmap<float, 4> msdf(glyphSize.Width, glyphSize.Height);
            msdfgen::generateMTSDF(msdf, shape, maxDist, 1.0, msdfgen::Vector2(0.0, 0.0));

            for (uint32_t y = 0; y < msdf.height(); y++) {
                for (uint32_t x = 0; x < msdf.width(); x++) {
                    float* pixel = msdf(x, y);
                    byte r = pixelFloatToByte(pixel[0]);
                    byte g = pixelFloatToByte(pixel[1]);
                    byte b = pixelFloatToByte(pixel[2]);
                    byte a = pixelFloatToByte(pixel[3]);
                    uint32_t pixelPos = (y + row * glyphSize.Height) * rowPitch + (x + column * glyphSize.Width) * pixelSize;
                    atlasData.Data[pixelPos] = r;
                    atlasData.Data[pixelPos + 1] = g;
                    atlasData.Data[pixelPos + 2] = b;
                    atlasData.Data[pixelPos + 3] = a;
                }
            }
            delete[] data;

            Glyph glyph = {
                {
                    column * glyphSize.Width + padding,
                    row * glyphSize.Height + padding,
                    (column + 1) * glyphSize.Width - padding,
                    (row + 1) * glyphSize.Height - padding
                },{
                    column * glyphSize.Width,
                    row * glyphSize.Height,
                    (column + 1) * glyphSize.Width,
                    (row + 1) * glyphSize.Height
                }
            };
            glyphs.set(c, glyph);
        }

        atlas->init(atlasData, atlasSize.Width, atlasSize.Height, DXGI_FORMAT_R8G8B8A8_UNORM);

        DeleteDC(hdcBmp);
        ReleaseDC(NULL, hdcScreen);
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

    FloatSize Font::measureText(const String& text) const {
        float measuredWidth = 0;
        for (size_t i = 0; i < text.Length; i++) {
            if (!glyphs.containsKey(text.get(i)))
                continue;

            const Glyph& glyph = glyphs.get(text.get(i));
            measuredWidth += glyph.tightRect.Width;
        }

        return { measuredWidth, (float)(getAscent() + getDescent()) };
    }
}