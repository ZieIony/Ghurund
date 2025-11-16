#include "ghuipch.h"
#include "Font.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"

#include "core/Finally.h"
#include "core/object/IntrusivePointer.h"
#include "TtfFile.h"

namespace Ghurund::UI {

	const Ghurund::Core::Type& Font::GET_TYPE() {
		static auto PROPERTY_FAMILYNAME = Property<Font, const WString&>("FamilyName", &getFamilyName);

		static const Ghurund::Core::Type TYPE = TypeBuilder<Font>()
			.withProperty(PROPERTY_FAMILYNAME)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void Font::initMetrics(HDC hdc) {
		GetTextMetrics(hdc, &tm);
	}

	inline void Font::init(const String& family, uint32_t weight, bool italic, const String& supportedCharacters) {
		this->familyName = family;
		this->weight = weight;
		this->italic = italic;

		HDC hdc = GetDC(NULL);

		float size = 12.0f;
		float lfHeight = -size * GetDeviceCaps(hdc, LOGPIXELSY) / 72.0f;
		HFONT hf = CreateFont((int)lfHeight, 0, 0, 0, weight, italic ? TRUE : FALSE, 0, 0, 0, 0, 0, CLEARTYPE_QUALITY, 0, familyName.getData());
		HGDIOBJ prevFont = SelectObject(hdc, hf);

		Finally f([&] {
			SelectObject(hdc, prevFont);
			ReleaseDC(NULL, hdc);
			DeleteObject(hf);
		});

		initMetrics(hdc);
		initKerning(hdc);
		initAtlas(hdc, supportedCharacters);
	}

	void Font::init(const void* data, size_t size, const String& supportedCharacters) {
		TtfFile file = {};
		file.init(data, size);
		String familyName = file.familyName;
		uint16_t weight = file.readFontWeight();
		bool italic = file.readFontItalic();
		DWORD numFonts = {};
		uninit();
		handle = AddFontMemResourceEx((void*)data, (DWORD)size, 0, &numFonts);
		init(familyName, weight, italic, supportedCharacters);
	}

	void Font::uninit() {
		atlas.set(nullptr);
		kerning.clear();
		if (handle != INVALID_HANDLE_VALUE) {
			RemoveFontMemResourceEx(handle);
			handle = INVALID_HANDLE_VALUE;
		}
	}

	void Font::initKerning(HDC hdc) {
		kerning.clear();
		DWORD result = GetKerningPairs(hdc, -1, nullptr);
		if (result == GDI_ERROR) {
			auto errorCode = GetLastError();
			throw InvalidParamException();
		} else if (result == 0) {
			Logger::log(LogType::INFO, _T("No kerning info for this font.\n"));
			return;
		}
		Array<KERNINGPAIR> kerningPairs(result);
		result = GetKerningPairs(hdc, (DWORD)kerningPairs.Size, &kerningPairs[0]);
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

	void Font::initAtlas(HDC hdc, const String& characters) {
		atlas = makeIntrusive<FontAtlas>();
		atlas->init(hdc, characters);
	}

	FloatSize Font::measureText(const String& text) const {
		float measuredWidth = 0;
		wchar_t prevC = 0;
		for (size_t i = 0; i < text.Length; i++) {
			wchar_t c = text.get(i);

			if (atlas->Glyphs.contains(c)) {
				const GlyphMetrics& glyph = atlas->Glyphs.get(c);
				measuredWidth += glyph.shapeSize.Width;
			}

			int k = getKerning(prevC, c);
			measuredWidth += k;

			prevC = c;
		}

		return { measuredWidth, (float)(Ascent + Descent) };
	}
}