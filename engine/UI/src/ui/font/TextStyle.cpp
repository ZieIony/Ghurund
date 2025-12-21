#include "ghuipch.h"
#include "TextStyle.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"

#include "core/Finally.h"
#include "core/object/IntrusivePointer.h"

namespace Ghurund::UI {

	const Ghurund::Core::Type& TextStyle::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<TextStyle>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void TextStyle::initMetrics(HDC hdc) {
		TEXTMETRIC tm;
		GetTextMetrics(hdc, &tm);
		fontMetrics = { (uint16_t)tm.tmHeight, (uint16_t)tm.tmAscent, (uint16_t)tm.tmDescent, (uint16_t)tm.tmWeight, (bool)tm.tmItalic };
	}

	inline void TextStyle::init(const String& family, float size, uint32_t weight, bool italic, const String& supportedCharacters) {
		this->size = size;

		HDC hdc = GetDC(NULL);

		float lfHeight = -size * GetDeviceCaps(hdc, LOGPIXELSY) / 72.0f;
		HFONT hf = CreateFont((int)lfHeight, 0, 0, 0, weight, italic ? TRUE : FALSE, 0, 0, 0, 0, 0, CLEARTYPE_QUALITY, 0, family.getData());
		HGDIOBJ prevFont = SelectObject(hdc, hf);

		Finally f([&] {
			SelectObject(hdc, prevFont);
			ReleaseDC(NULL, hdc);
			DeleteObject(hf);
		});

		initMetrics(hdc);
		kerning.init(hdc);
		initAtlas(hdc, supportedCharacters);
	}

	void TextStyle::init(const Font& font, float size, const String& supportedCharacters) {
		init(font.FamilyName, size, font.Weight, font.Italic, supportedCharacters);
	}

	void TextStyle::uninit() {
		atlas.set(nullptr);
	}

	void TextStyle::initAtlas(HDC hdc, const String& characters) {
		atlas = makeIntrusive<FontAtlas>();
		atlas->init(hdc, characters);
	}

	FloatSize TextStyle::measureText(const String& text) const {
		float measuredWidth = 0;
		wchar_t prevC = 0;
		for (size_t i = 0; i < text.Length; i++) {
			wchar_t c = text.get(i);

			if (atlas->Glyphs.contains(c)) {
				const GlyphMetrics& glyph = atlas->Glyphs.get(c);
				measuredWidth += glyph.shapeSize.Width;
			}

			int k = Kerning.get(prevC, c);
			measuredWidth += k;

			prevC = c;
		}

		return { measuredWidth, (float)fontMetrics.height };
	}
}