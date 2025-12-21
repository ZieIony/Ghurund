#include "ghuipch.h"
#include "TextLine.h"

namespace Ghurund::UI {
	void TextLine::add(const CharacterInfo& info, const TextStyle* textStyle, const Color& color) {
		characters.add(info);
		if (metrics.Empty) {
			metrics.add({ textStyle->FontMetrics.ascent, textStyle->FontMetrics.descent });
			WString text;
			text.add(info.c);
			spans.add({ 0, 1, textStyle, color });
		} else {
			auto& currentSpan = spans[spans.Size - 1];
			if (currentSpan.textStyle != textStyle || currentSpan.color != color) {
				uint16_t a = std::max(metrics[metrics.Size - 1].ascent, textStyle->FontMetrics.ascent);
				uint16_t d = std::max(metrics[metrics.Size - 1].descent, textStyle->FontMetrics.descent);
				metrics.add({ a, d });
				spans.add({ characters.Size - 1, characters.Size, textStyle, color });
			} else {
				currentSpan.finish++;
			}
		}
	}

	TextLine TextLine::breakLine(bool breakWords) {
		for (size_t j = 0; j < characters.Size; j++) {
			size_t i = characters.Size - j - 1;
			if (isSpace(characters[i].c)) {
				TextLine nextLine;
				uint32_t zero = characters[i + 1].pos.x;
				TextSpan* currentSpan = &spans[0];
				size_t currentSpanIndex = 0;
				for (size_t k = 0; k < spans.Size; i++) {
					if (spans[k].start <= i + 1 && spans[k].finish > i + 1) {
						currentSpanIndex = k;
						currentSpan = &spans[currentSpanIndex];
						break;
					}
				}
				for (size_t k = i + 1; k < characters.Size; k++) {
					if (k == currentSpan->finish) {
						currentSpanIndex++;
						currentSpan = &spans[currentSpanIndex];
					}
					CharacterInfo& c = characters[k];
					c.pos.x -= zero;
					nextLine.add(c, currentSpan->textStyle, currentSpan->color);
				}

				size_t toRemove = characters.Size - i;
				characters.removeRange(i, characters.Size);

				while (toRemove > 0) {
					auto& currentSpan = spans[spans.Size - 1];
					if (currentSpan.finish - currentSpan.start <= toRemove) {
						toRemove -= currentSpan.finish - currentSpan.start;
						spans.removeAt(spans.Size - 1);
						metrics.removeAt(metrics.Size - 1);
					} else {
						currentSpan.finish -= toRemove;
						break;
					}
				}
				for (auto& info : nextLine.Characters)
					info.pos.y += Height;
				return nextLine;
			}
		}

		if (characters.Size > 1) {
			TextLine nextLine;
			if (breakWords) {
				CharacterInfo& c = characters[characters.Size - 1];
				auto& span = spans[spans.Size - 1];
				nextLine.add(c, span.textStyle, span.color);
				characters.removeAt(characters.Size - 1);
				if (span.finish - span.start > 1) {
					span.finish--;
				} else {
					spans.removeAt(spans.Size - 1);
					metrics.removeAt(metrics.Size - 1);
				}
				nextLine.Characters[0].pos.x = 0;
				nextLine.Characters[0].pos.y += Height;
			}
			return nextLine;
		} else {
			return TextLine();
		}
	}

	void TextLine::align(TextAlignment alignment) {

	}
}