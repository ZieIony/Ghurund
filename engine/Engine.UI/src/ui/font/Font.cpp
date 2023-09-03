#include "ghuipch.h"
#include "Font.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"

#include "core/Finally.h"
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

	msdfgen::Shape shapeFromPolygonData(uint8_t* data, DWORD size, GLYPHMETRICS& glyphMetrics, IntSize glyphSize, uint32_t padding) {
		auto tx = [&](float x) {
			float offset = (std::max(glyphMetrics.gmBlackBoxX, glyphMetrics.gmBlackBoxY) - glyphMetrics.gmBlackBoxX) / 2.0f;
			return (x - glyphMetrics.gmptGlyphOrigin.x + offset) / std::max(glyphMetrics.gmBlackBoxX, glyphMetrics.gmBlackBoxY) * (glyphSize.Width - padding * 2) + padding;
			};
		auto ty = [&](float y) {
			float offset = (std::max(glyphMetrics.gmBlackBoxX, glyphMetrics.gmBlackBoxY) - glyphMetrics.gmBlackBoxY) / 2.0f;
			return (glyphMetrics.gmptGlyphOrigin.y - y - offset) / std::max(glyphMetrics.gmBlackBoxX, glyphMetrics.gmBlackBoxY) * (glyphSize.Height - padding * 2) + padding;
			};

		msdfgen::Shape shape;
		uint8_t* ptr = data;
		size_t polys = 0;
		while (ptr < data + size) {
			size_t leftPolys = data + size - ptr;
			TTPOLYGONHEADER header = *(TTPOLYGONHEADER*)ptr;
			if (header.dwType != TT_POLYGON_TYPE)
				throw InvalidDataException("polygon type is not TT_POLYGON_TYPE");
			uint8_t* endPoly = ptr + header.cb;
			ptr += sizeof(TTPOLYGONHEADER);
			msdfgen::Point2 start = fromFixed(header.pfxStart);
			msdfgen::Point2 current = start;

			// read primitives of this polygon
			msdfgen::Contour contour;
			size_t curves = 0;
			while (ptr < endPoly) {
				size_t leftCurves = endPoly - ptr;
				List<BezierCubic> beziers;
				TTPOLYCURVE* curve = (TTPOLYCURVE*)ptr;
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
					for (size_t j = 0; j < curve->cpfx; j += 3) {
						msdfgen::Point2 p2 = fromFixed(curve->apfx[j]);
						msdfgen::Point2 p3 = fromFixed(curve->apfx[j + 1]);
						msdfgen::Point2 p4 = fromFixed(curve->apfx[j + 2]);
						contour.addEdge(new msdfgen::CubicSegment(current, p2, p3, p4));
						current = p4;
					}
				} else {
					auto type = curve->wType;
				}
				size_t curveSize = sizeof(TTPOLYCURVE) + (curve->cpfx - 1) * sizeof(POINTFX);
				ptr += curveSize;
				curves++;
			}
			if (ptr != endPoly)
				throw InvalidDataException("invalid poly size");
			if (start != current)
				contour.addEdge(new msdfgen::LinearSegment({ tx(current.x),ty(current.y) }, { tx(start.x),ty(start.y) }));
			shape.addContour(contour);
			polys++;
		}
		if (ptr != data + size)
			throw InvalidDataException("invalid shape size");

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

		Finally f([&] {
			ReleaseDC(NULL, hdcScreen);
			DeleteObject(hf);
			});

		GetTextMetrics(hdcScreen,&tm);
		initKerning(hf);

		initMsdf(hf, supportedCharacters);
	}

	void Font::init(const void* data, size_t size, const String& supportedCharacters) {
		TtfFile file = {};
		file.init(data, size);
		String familyName = file.readFontFamilyName();
		uint16_t weight = file.readFontWeight();
		bool italic = file.readFontItalic();
		DWORD numFonts = {};
		uninit();
		handle = AddFontMemResourceEx((void*)data, size, 0, &numFonts);
		init(familyName, weight, italic, supportedCharacters);
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
		HGDIOBJ prevFont = SelectObject(hdcBmp, hf);

		Finally f([&] {
			SelectObject(hdcBmp, prevFont);
			DeleteDC(hdcBmp);
			ReleaseDC(NULL, hdcScreen);
			});

		kerning.clear();
		DWORD result = GetKerningPairs(hdcBmp, 0, nullptr);
		if (result == GDI_ERROR) {
			auto errorCode = GetLastError();
			throw InvalidParamException();
		}
		Array<KERNINGPAIR> kerningPairs(result);
		result = GetKerningPairs(hdcBmp, kerningPairs.Size, &kerningPairs[0]);
		if (result == GDI_ERROR) {
			auto errorCode = GetLastError();
			throw InvalidParamException();
		}
		for (auto& kerningPair : kerningPairs) {
			size_t index = kerning.indexOfKey(kerningPair.wFirst);
			if (index == kerning.Size) {
				Map<tchar, int> map;
				map.set(kerningPair.wSecond, kerningPair.iKernAmount);
				kerning.set(kerningPair.wFirst, map);
			} else {
				kerning.getValue(index).set(kerningPair.wSecond, kerningPair.iKernAmount);
			}
		}
	}

	void Font::getGlyphs(HFONT hf, const String& characters) {
		HDC hdcScreen = GetDC(NULL);
		HDC hdcBmp = CreateCompatibleDC(hdcScreen);
		HGDIOBJ prevFont = SelectObject(hdcBmp, hf);

		Finally f([&] {
			SelectObject(hdcBmp, prevFont);
			DeleteDC(hdcBmp);
			ReleaseDC(NULL, hdcScreen);
			});

		glyphs.clear();
		for (size_t i = 0; i < characters.Length; i++) {
			tchar c = characters[i];
			GLYPHMETRICS glyphMetrics = {};
			MAT2 mat = { { 0, 1 },{ 0, 0 },{ 0, 0 },{ 0, 1 } };
			DWORD result = GetGlyphOutline(hdcBmp, c, GGO_METRICS, &glyphMetrics, 0, nullptr, &mat);
			if (result == GDI_ERROR)
				throw InvalidParamException();

			float scale = BITMAP_SIZE / (float)(Ascent + Descent);
			Glyph glyph = {
				{
					glyphMetrics.gmBlackBoxX,
					glyphMetrics.gmBlackBoxY
				},{
					(uint32_t)std::ceilf(glyphMetrics.gmBlackBoxX * scale),
					(uint32_t)std::ceilf(glyphMetrics.gmBlackBoxY * scale)
				},{
					0,
					0
				}
			};
			glyphs.set(c, glyph);
		}
	}

	bool Font::fitAllGlyphs(uint32_t width, uint32_t height) {
		uint32_t currentWidth = PADDING, currentHeight = PADDING, maxRowHeight = 0;
		for (auto& pair : glyphs) {
			if (currentHeight + pair.value.bitmapSize.Height + PADDING > height)
				return false;
			pair.value.offset.x = currentWidth;
			pair.value.offset.y = currentHeight;
			currentWidth += pair.value.bitmapSize.Width + PADDING;
			maxRowHeight = std::max(maxRowHeight, pair.value.bitmapSize.Height);
			if (currentWidth > width) {
				currentWidth = pair.value.bitmapSize.Width + PADDING * 2;
				currentHeight += maxRowHeight + PADDING;
				pair.value.offset.x = 0;
				pair.value.offset.y = currentHeight;
				maxRowHeight = 0;
			}
		}
		return true;
	}

	IntSize Font::getAtlasSize() {
		std::sort(glyphs.begin(), glyphs.end(), [](KeyValuePair<tchar, Glyph>& first, KeyValuePair<tchar, Glyph>& second) {
			return first.value.bitmapSize.Height > second.value.bitmapSize.Height;
			});
		uint32_t width = std::bit_ceil(PADDING * 2 + glyphs.getValue(0).bitmapSize.Width);
		uint32_t height = width;
		while (true) {
			if (fitAllGlyphs(width, height))
				return { width, height };
			if (width > height) {
				height = width;
			} else {
				width *= 2;
			}
		}
	}

	void Font::initMsdf(HFONT hf, const String& characters) {
		HDC hdcScreen = GetDC(NULL);
		HDC hdcBmp = CreateCompatibleDC(hdcScreen);
		HGDIOBJ prevFont = SelectObject(hdcBmp, hf);

		Finally f([&] {
			SelectObject(hdcBmp, prevFont);
			DeleteDC(hdcBmp);
			ReleaseDC(NULL, hdcScreen);
			});

		getGlyphs(hf, characters);
		IntSize atlasSize = getAtlasSize();
		uint32_t pixelSize = ImageLoader::getDXGIFormatBitsPerPixel(DXGI_FORMAT_R8G8B8A8_UNORM) / 8;
		uint32_t rowPitch = pixelSize * atlasSize.Width;
		Buffer atlasData(rowPitch * atlasSize.Height);
		if (atlas)
			atlas->release();
		atlas = ghnew Image();

		uint32_t maxDist = 8;
		for (tchar c : characters) {

			GLYPHMETRICS glyphMetrics = {};
			MAT2 mat = { {0, 1}, {0, 0}, {0, 0}, {0, 1} };
			DWORD result = GetGlyphOutline(hdcBmp, c, GGO_NATIVE, &glyphMetrics, 0, nullptr, &mat);
			if (result == GDI_ERROR)
				throw InvalidParamException();
			DWORD size = result;
			Buffer glyphOutlineData(size);
			result = GetGlyphOutline(hdcBmp, c, GGO_NATIVE, &glyphMetrics, glyphOutlineData.Size, glyphOutlineData.Data, &mat);
			if (result == GDI_ERROR)
				throw InvalidParamException();

			Glyph glyph = glyphs.get(c);
			msdfgen::Shape shape = shapeFromPolygonData(glyphOutlineData.Data, glyphOutlineData.Size, glyphMetrics, glyph.bitmapSize, maxDist + PADDING);

			// whitespace characters don't have any shape data
			if (shape.contours.size() > 0) {
				shape.normalize();
				msdfgen::edgeColoringByDistance(shape, 3);
				msdfgen::Bitmap<float, 4> msdf(glyph.bitmapSize.Width, glyph.bitmapSize.Height);
				msdfgen::generateMTSDF(msdf, shape, maxDist, 1.0, msdfgen::Vector2(0.0, 0.0));

				for (uint32_t y = 0; y < msdf.height(); y++) {
					for (uint32_t x = 0; x < msdf.width(); x++) {
						float* pixel = msdf(x, y);
						byte r = pixelFloatToByte(pixel[0]);
						byte g = pixelFloatToByte(pixel[1]);
						byte b = pixelFloatToByte(pixel[2]);
						byte a = pixelFloatToByte(pixel[3]);
						uint32_t pixelPos = (y + glyph.offset.y) * rowPitch + (x + glyph.offset.x) * pixelSize;
						atlasData.Data[pixelPos] = r;
						atlasData.Data[pixelPos + 1] = g;
						atlasData.Data[pixelPos + 2] = b;
						atlasData.Data[pixelPos + 3] = a;
					}
				}
			}
		}

		atlas->init(atlasData, atlasSize.Width, atlasSize.Height, DXGI_FORMAT_R8G8B8A8_UNORM);
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
			measuredWidth += glyph.shapeSize.Width;
		}

		return { measuredWidth, (float)(Ascent + Descent) };
	}
}