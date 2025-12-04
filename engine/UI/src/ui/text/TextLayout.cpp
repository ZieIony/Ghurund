#include "ghuipch.h"
#include "TextLayout.h"

#include "core/math/Rect.h"
#include "engine/graphics/RenderGroup.h"

namespace Ghurund::UI {
	void TextLayout::refresh() {
		lines.clear();
		List<CharacterInfo> line;
		wchar_t prevC = 0;
		float prevX = 0, y = 0;
		for (size_t i = 0; i < text.Length; i++) {
			wchar_t c = text.charAt(i);
			auto format = text.getTextFormat(i);
			if (!format)
				format = this->format;
			auto color = getColor(i);
			auto it = format->Font->Atlas->Glyphs.find(c);
			if (it != format->Font->Atlas->Glyphs.end()) {
				auto glyph = it->value;
				line.add(CharacterInfo(c, i, { prevX, y }, glyph, color, format));
				int kerning = format->Font->getKerning(prevC, c);

				if (prevX + glyph.shapeSize.Width > size.Width) {
					breakLine(line);
					prevX = 0;
					y += format->Font->Height;
				} else {
					prevX += glyph.shapeSize.Width + kerning;
				}
				prevC = c;
			}
		}
		lines.add(line);
		valid = true;
	}

	void TextLayout::breakLine(List<CharacterInfo> &line) {
		for (size_t j = 0; j < line.Size; j++) {
			size_t i = line.Size - j - 1;
			if (std::isspace(line.get(i).c)) {
				List<CharacterInfo> firstPart = line.sublist(0, i);
				lines.add(firstPart);
				line.removeRange(0, i + 1);
				return;
			}
		}

		// there's no whitespace in the line, just take as many characters as possible
		float width = 0.0f;
		float s = format->Size / format->Font->Height;
		for (size_t i = 0; i < line.Size; i++) {
			CharacterInfo& c = line.get(i);
			width += c.glyph.shapeSize.Width * s;
			if (width > size.Width) {
				List<CharacterInfo> firstPart = line.sublist(0, i);
				lines.add(firstPart);
				line.removeRange(0, i + 1);
				return;
			}
		}

		// one character is too much - just take it
		lines.add(line);
		line.clear();
	}

	HitTestMetrics TextLayout::hitTestTextPosition(uint32_t textPosition, bool isTrailingHit, float* pointX, float* pointY) {
		return {};
	}

	Ghurund::Core::Array<HitTestMetrics> TextLayout::hitTestTextRange(uint32_t textPosition, uint32_t textLength, float originX, float originY) {
		return {};
	}

	HitTestMetrics TextLayout::hitTestPoint(float pointX, float pointY, bool* isTrailingHit) {
		return {};
	}

	Ghurund::Core::Array<Ghurund::UI::LineMetrics> TextLayout::getLineMetrics() {
		return {};
	}

	Ghurund::Core::Array<Ghurund::UI::ClusterMetrics> TextLayout::getClusterMetrics() {
		return {};
	}

	void TextLayout::insertTextAt(uint32_t position, const Ghurund::Core::WString& textToInsert) {
		text.insert(position, textToInsert);
	}

	void TextLayout::removeTextAt(uint32_t position, uint32_t lengthToRemove) {
		text.remove(position, lengthToRemove);
	}

	Ghurund::Core::Color TextLayout::getColor(uint32_t pos) {
		return Color;
	}

	Ghurund::UI::TextFormat* TextLayout::getFormat(uint32_t position) {
		return nullptr;
	}

	TextMetrics TextLayout::getMetrics() {
		return {};
	}

	void TextLayout::draw(RenderGroup& group) {
		if (!format || !format->Font)
			return;
		if (!valid)
			refresh();
		for (auto& line : lines) {
			for (auto& character : line) {
				FloatRect src = {
					character.glyph.bitmapPos.x,
					character.glyph.bitmapPos.y,
					character.glyph.bitmapPos.x + character.glyph.bitmapSize.Width,
					character.glyph.bitmapPos.y + character.glyph.bitmapSize.Height
				};
				//canvas.save();
				float s = format->Size / 32;
				//canvas.scale(s, s);
				/*canvas.translate(
					character.pos.x,
					character.pos.y + format->Font->Ascent - character.glyph.shapeOrigin.y
				);*/
				Ghurund::Core::Color color = character.color;
				//canvas.drawImage(*atlas, src);
				/*canvas.Color = Ghurund::Core::Color(0xffff0000);
				canvas.drawRect(0, 0, character.glyph.bitmapSize.Width, character.glyph.bitmapSize.Height, 1.0f);
				canvas.Color = Ghurund::Core::Color(0xff00ff00);
				canvas.drawLine(
					0,
					format->Font->Ascent,
					character.glyph.bitmapSize.Width,
					format->Font->Ascent,
					1.0f
				);
				canvas.restore();*/
			}
		}
		//canvas.Color = Ghurund::Core::Color(0xff0000ff);
		//canvas.drawRect(0, 0, Size.Width, Size.Height, 1.0f);
	}

	uint32_t TextLayout::measureWidth() {
		size.Width = 10000;
		if (!valid)
			refresh();
		uint32_t width = 0;
		for (auto& line : lines) {
			for (auto& c : line) {
				width += c.glyph.shapeSize.Width;
			}
		}
		float s = format->Size / format->Font->Height;
		return width * s;
	}

	uint32_t TextLayout::measureHeight() {
		if (!valid)
			refresh();
		/*uint32_t height = 0;
		for (auto& line : lines) {
			for (auto& c : line) {
				height = std::max(height, c.glyph.shapeSize.Height);
			}
		}*/
		return format->Size;
	}
}
