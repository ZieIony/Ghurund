#include "ghuipch.h"
#include "Font.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"

#include "core/Finally.h"
#include "core/object/IntrusivePointer.h"
#include "core/image/ImageLoader.h"
#include "core/math/Bezier.h"
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
		auto tx = [&](double x) {
			double offset = (std::max(glyphMetrics.gmBlackBoxX, glyphMetrics.gmBlackBoxY) - glyphMetrics.gmBlackBoxX) / 2.0f;
			return (x - glyphMetrics.gmptGlyphOrigin.x + offset) / std::max(glyphMetrics.gmBlackBoxX, glyphMetrics.gmBlackBoxY) * (glyphSize.Width - padding * 2) + padding;
			};
		auto ty = [&](double y) {
			double offset = (std::max(glyphMetrics.gmBlackBoxX, glyphMetrics.gmBlackBoxY) - glyphMetrics.gmBlackBoxY) / 2.0f;
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

		static const Ghurund::Core::Type TYPE = TypeBuilder<Font>()
			.withProperty(PROPERTY_FAMILYNAME)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void Font::initAtlas(const String& supportedCharacters, const IBitmapFactory& bitmapFactory) {
		HDC hdcScreen = GetDC(NULL);

		float size = 12.0f;
		float lfHeight = -size * GetDeviceCaps(hdcScreen, LOGPIXELSY) / 72.0f;
		HFONT hf = CreateFont((int)lfHeight, 0, 0, 0, weight, italic ? TRUE : FALSE, 0, 0, 0, 0, 0, CLEARTYPE_QUALITY, 0, familyName.getData());

		Finally f([&] {
			ReleaseDC(NULL, hdcScreen);
			DeleteObject(hf);
			});

		GetTextMetrics(hdcScreen, &tm);
		initKerning(hf);

		initMsdf(hf, supportedCharacters, bitmapFactory);
	}

	void Font::init(const IBitmapFactory& bitmapFactory, const void* data, size_t size, const String& supportedCharacters) {
		TtfFile file = {};
		file.init(data, size);
		String familyName = file.familyName;
		uint16_t weight = file.readFontWeight();
		bool italic = file.readFontItalic();
		DWORD numFonts = {};
		uninit();
		handle = AddFontMemResourceEx((void*)data, (DWORD)size, 0, &numFonts);
		init(bitmapFactory, familyName, weight, italic, supportedCharacters);
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
		result = GetKerningPairs(hdcBmp, (DWORD)kerningPairs.Size, &kerningPairs[0]);
		if (result == GDI_ERROR) {
			auto errorCode = GetLastError();
			throw InvalidParamException();
		}
		for (auto& kerningPair : kerningPairs) {
			auto it = kerning.find(kerningPair.wFirst);
			if (it == kerning.end()) {
				Map<tchar, int> map;
				map.put(kerningPair.wSecond, kerningPair.iKernAmount);
				kerning.put(kerningPair.wFirst, map);
			} else {
				it->value.put(kerningPair.wSecond, kerningPair.iKernAmount);
			}
		}
	}

	void Font::initGlyphs(HFONT hf, const String& characters) {
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

			float scale = (BITMAP_SIZE - 2 * PADDING - 2 * MAX_DIST) / (float)Height;
			Glyph glyph = {
				.shapeSize = {
					glyphMetrics.gmBlackBoxX,
					glyphMetrics.gmBlackBoxY
				},
				.bitmapSize = {
					(uint32_t)std::ceilf(glyphMetrics.gmBlackBoxX * scale),
					(uint32_t)std::ceilf(glyphMetrics.gmBlackBoxY * scale)
				},
				.originY = glyphMetrics.gmptGlyphOrigin.y,
				.offset{
					glyphMetrics.gmptGlyphOrigin.x,
					glyphMetrics.gmptGlyphOrigin.y
				}
			};
			glyphs.put(c, glyph);
		}
	}

	bool Font::fitAllGlyphs(const List<Glyph*>& sortedGlyphs, uint32_t width, uint32_t height) {
		uint32_t currentWidth = PADDING, currentHeight = PADDING, maxRowHeight = 0;
		for (Glyph* glyph : sortedGlyphs) {
			if (currentHeight + glyph->bitmapSize.Height + PADDING > height)
				return false;
			glyph->offset.x = currentWidth;
			glyph->offset.y = currentHeight;
			currentWidth += glyph->bitmapSize.Width + PADDING;
			maxRowHeight = std::max(maxRowHeight, glyph->bitmapSize.Height);
			if (currentWidth > width) {
				currentWidth = glyph->bitmapSize.Width + PADDING * 2;
				currentHeight += maxRowHeight + PADDING;
				glyph->offset.x = 0;
				glyph->offset.y = currentHeight;
				maxRowHeight = 0;
			}
		}
		return true;
	}

	IntSize Font::getAtlasSize() {
		List<Glyph*> sortedGlyphs;
		for (auto& [c, glyph] : glyphs)
			sortedGlyphs.add(&glyph);
		std::sort(sortedGlyphs.begin(), sortedGlyphs.end(), [](Glyph* first, Glyph* second) {
			return first->bitmapSize.Height > second->bitmapSize.Height;
			});
		uint32_t width = std::bit_ceil(PADDING * 2 + glyphs.begin()->value.bitmapSize.Width);
		uint32_t height = width;
		while (true) {
			if (fitAllGlyphs(sortedGlyphs, width, height))
				return { width, height };
			if (width > height) {
				height = width;
			} else {
				width *= 2;
			}
		}
	}

	void Font::initMsdf(HFONT hf, const String& characters, const IBitmapFactory& bitmapFactory) {
		HDC hdcScreen = GetDC(NULL);
		HDC hdcBmp = CreateCompatibleDC(hdcScreen);
		HGDIOBJ prevFont = SelectObject(hdcBmp, hf);

		Finally f([&] {
			SelectObject(hdcBmp, prevFont);
			DeleteDC(hdcBmp);
			ReleaseDC(NULL, hdcScreen);
			});

		initGlyphs(hf, characters);
		IntSize atlasSize = getAtlasSize();
		uint32_t pixelSize = ImageLoader::getDXGIFormatBitsPerPixel(DXGI_FORMAT_R8G8B8A8_UNORM) / 8;
		uint32_t rowPitch = pixelSize * atlasSize.Width;
		Buffer atlasData(rowPitch * atlasSize.Height);
		if (atlas)
			atlas->release();
		IntrusivePointer<Image> atlasImage = makeIntrusive<Image>();

		for (tchar c : characters) {

			GLYPHMETRICS glyphMetrics = {};
			MAT2 mat = { {0, 1}, {0, 0}, {0, 0}, {0, 1} };
			DWORD result = GetGlyphOutline(hdcBmp, c, GGO_NATIVE, &glyphMetrics, 0, nullptr, &mat);
			if (result == GDI_ERROR)
				throw InvalidParamException();
			DWORD size = result;
			Buffer glyphOutlineData(size);
			result = GetGlyphOutline(hdcBmp, c, GGO_NATIVE, &glyphMetrics, (DWORD)glyphOutlineData.Size, glyphOutlineData.Data, &mat);
			if (result == GDI_ERROR)
				throw InvalidParamException();

			Glyph glyph = glyphs.get(c);
			msdfgen::Shape shape = shapeFromPolygonData(glyphOutlineData.Data, (DWORD)glyphOutlineData.Size, glyphMetrics, glyph.bitmapSize, MAX_DIST + PADDING);

			// whitespace characters don't have any shape data
			if (shape.contours.size() > 0) {
				shape.normalize();
				msdfgen::edgeColoringByDistance(shape, 3);
				msdfgen::Bitmap<float, 4> msdf(glyph.bitmapSize.Width, glyph.bitmapSize.Height);
				msdfgen::generateMTSDF(msdf, shape, MAX_DIST, 1.0, msdfgen::Vector2(0.0, 0.0));

				for (uint32_t y = 0; y < (uint32_t)msdf.height(); y++) {
					for (uint32_t x = 0; x < (uint32_t)msdf.width(); x++) {
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

		atlasImage->init(atlasData, atlasSize.Width, atlasSize.Height, DXGI_FORMAT_R8G8B8A8_UNORM);
		atlas = bitmapFactory.makeBitmap(*atlasImage.get());
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
		wchar_t prevC = 0;
		for (size_t i = 0; i < text.Length; i++) {
			wchar_t c = text.get(i);

			if (glyphs.contains(c)) {
				const Glyph& glyph = glyphs.get(text.get(i));
				measuredWidth += glyph.shapeSize.Width;
			}

			int k = getKerning(prevC, c);
			measuredWidth += k;

			prevC = c;
		}

		return { measuredWidth, (float)(Ascent + Descent) };
	}
}