#pragma once

#include "CharacterInfo.h"
#include "TextSpan.h"

#include "ui/font/GlyphMetrics.h"
#include "ui/font/Font.h"

#include <DirectXMath.h>

namespace Ghurund::UI {
	class TextLine {
	private:
		List<CharacterInfo> characters;
		List<uint32_t> heights;
		List<TextSpan> spans;

	public:
		inline uint32_t getWidth() const {
			auto& c = characters[characters.Size - 1];
			return uint32_t(c.pos.x + c.glyph.shapeSize.Width);
		}

		__declspec(property(get = getWidth)) uint32_t Width;

		inline uint32_t getHeight() const {
			return heights.Empty ? 0 : heights[heights.Size - 1];
		}

		__declspec(property(get = getHeight)) uint32_t Height;

		inline bool getIsEmpty() const {
			return characters.Empty;
		}

		__declspec(property(get = getIsEmpty)) bool IsEmpty;

		inline const List<TextSpan>& getSpans() const {
			return spans;
		}

		__declspec(property(get = getSpans)) const List<TextSpan>& Spans;

		inline const List<CharacterInfo>& getCharacters() const {
			return characters;
		}

		__declspec(property(get = getCharacters)) const List<CharacterInfo>& Characters;

		void add(const CharacterInfo& info, const Font* font, const Color& color);

		TextLine breakLine(bool breakWords);
	};
}