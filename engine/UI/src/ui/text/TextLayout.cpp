#include "ghuipch.h"
#include "TextLayout.h"

#include "engine/graphics/RenderGroup.h"

namespace Ghurund::UI {
	void TextLayout::refresh() {
		lines.clear();
		if (!document)
			return;

		TextLine line;
		wchar_t prevC = '\0';
		float x = 0, y = 0;
		for (size_t i = 0; i < document->Length; i++) {
			wchar_t c = document->charAt(i);
			auto font = document->getFont(i);
			auto color = document->getTextColor(i);
			auto it = font->Atlas->Glyphs.find(c);
			if (c == '\n') {
				x = 0;
				if (line.IsEmpty) {
					y += font->Height;
				} else {
					y += line.Height;
					lines.add(line);
					line = TextLine();
				}
				prevC = c;
				continue;
			}
			if (it == font->Atlas->Glyphs.end()) {
				Logger::log(LogType::WARNING, std::format(_T("Font doesn't contain glyph definition for character '{}'.\n"), c).c_str());
				prevC = c;
				continue;
			}

			auto& glyph = it->value;
			line.add(CharacterInfo(c, { x, y }, glyph), font, color);

			if (x + glyph.shapeSize.Width > preferredSize.Width) {
				TextLine nextLine = line.breakLine(breakWords);
				if (nextLine.IsEmpty) {
					int kerning = font->getKerning(prevC, c);
					x += glyph.increment + kerning;
					prevC = c;
				} else {
					lines.add(line);
					auto& info = nextLine.Characters[nextLine.Characters.Size - 1];
					x = info.pos.x + info.glyph.increment;
					y += line.Height;
					prevC = '\0';
					line = nextLine;
				}
			} else {
				int kerning = font->getKerning(prevC, c);
				x += glyph.increment + kerning;
				prevC = c;
			}
		}
		lines.add(line);
		valid = true;
	}

	void TextLayout::initMeshes(ITextMeshFactory& textMeshFactory, IMaterial* material) {
		textMeshes.clear();
		for (auto& line : lines) {
			for (auto& span : line.Spans) {
				auto mesh = IntrusivePointer<Resource>(textMeshFactory.makeMesh(line.Characters, span));
				material->addReference();
				XMFLOAT3 pos = { line.Characters[0].pos.x, line.Characters[0].pos.y, 0 };
				textMeshes.add(DrawPacket{
					mesh,
					IntrusivePointer<IMaterial>(material),
					pos
				});
			}
		}
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
		document->insert(position, textToInsert);
	}

	void TextLayout::removeTextAt(uint32_t position, uint32_t lengthToRemove) {
		document->remove(position, lengthToRemove);
	}

	TextMetrics TextLayout::getMetrics() {
		return {};
	}

	void TextLayout::draw(RenderGroup& group) {
		if (!valid)
			refresh();
		group.objects.addAll(textMeshes);
	}

	uint32_t TextLayout::measureWidth() {
		size.Width = 0;
		if (!valid)
			refresh();
		uint32_t width = 0;
		for (auto& line : lines)
			size.Width = std::max(size.Width, line.Width);
		float s = 1;//font->Size / font->Font->Height;
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
		return 0;// font->Size;
	}

#ifdef _DEBUG
	bool TextLayout::validate() const {
		float x = -1, y = -1;
		for (auto& line : lines) {
			for (auto& info : line.Characters) {
				if (info.pos.x <= x)
					return false;
				x = info.pos.x;
				if (info.pos.y <= y)
					return false;
			}
			x = -1;
			y = line.Characters[0].pos.y;
		}
		return true;
	}
#endif
}
