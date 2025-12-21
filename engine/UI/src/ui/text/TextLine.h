#pragma once

#include "CharacterInfo.h"
#include "TextAlignment.h"
#include "TextSpan.h"

#include "ui/font/GlyphMetrics.h"
#include "ui/font/TextStyle.h"

#include <DirectXMath.h>

namespace Ghurund::UI {
	class TextLine {
	private:
		struct LineMetrics {
			uint16_t ascent, descent;
		};

		List<CharacterInfo> characters;
		List<LineMetrics> metrics;
		List<TextSpan> spans;

	public:
		inline uint32_t getWidth() const {
			if (characters.Empty)
				return 0;
			auto& c = characters[characters.Size - 1];
			return uint32_t(c.pos.x + c.glyph.shapeSize.Width);
		}

		__declspec(property(get = getWidth)) uint32_t Width;

		inline uint16_t getAscent() const {
			return metrics.Empty ? 0 : metrics[metrics.Size - 1].ascent;
		}

		__declspec(property(get = getAscent)) uint16_t Ascent;

		inline uint16_t getDescent() const {
			return metrics.Empty ? 0 : metrics[metrics.Size - 1].descent;
		}

		__declspec(property(get = getDescent)) uint16_t Descent;

		inline uint16_t getHeight() const {
			return metrics.Empty ? 0 : (metrics[metrics.Size - 1].ascent + metrics[metrics.Size - 1].descent);
		}

		__declspec(property(get = getHeight)) uint16_t Height;

		inline uint16_t getBaseline() const {
			return metrics.Empty ? 0 : metrics[metrics.Size - 1].ascent;
		}

		__declspec(property(get = getBaseline)) uint16_t Baseline;

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

		void add(const CharacterInfo& info, const TextStyle* textStyle, const Color& color);

		TextLine breakLine(bool breakWords);

		void align(TextAlignment alignment);
	};
}