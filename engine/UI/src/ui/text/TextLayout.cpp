#include "ghuipch.h"
#include "TextLayout.h"

#include "engine/graphics/RenderGroup.h"
#include "engine/parameter/TextureParameter.h"
#include <engine/parameter/ValueParameter.h>

namespace Ghurund::UI {
	void TextLayout::refresh() {
		lines.clear();
		size = { 0, 0 };
		if (!document)
			return;

		TextLine line;
		wchar_t prevC = '\0';
		float x = 0;
		uint32_t height = 0;
		for (size_t i = 0; i < document->Length; i++) {
			wchar_t c = document->charAt(i);
			auto textStyle = document->getTextStyle(i);
			auto color = document->getTextColor(i);
			auto it = textStyle->Atlas->Glyphs.find(c);
			if (c == '\n') {
				x = 0;
				height += textStyle->FontMetrics.height;
				if (!line.IsEmpty) {
					size.Width = std::max(size.Width, line.Width);
					lines.add(line);
					line = TextLine();
				}
				prevC = c;
				continue;
			}
			if (it == textStyle->Atlas->Glyphs.end()) {
				Logger::log(LogType::WARNING, std::format(_T("Font doesn't contain glyph definition for character '{}'.\n"), c).c_str());
				prevC = c;
				continue;
			}

			auto& glyph = it->value;
			line.add(CharacterInfo(c, { x, 0 }, glyph), textStyle, color);

			if (x + glyph.shapeSize.Width > preferredSize.Width) {
				TextLine nextLine = line.breakLine(breakWords);
				if (nextLine.IsEmpty) {
					int kerning = textStyle->Kerning.get(prevC, c);
					x += glyph.increment + kerning;
					prevC = c;
				} else {
					size.Width = std::max(size.Width, line.Width);
					lines.add(line);
					auto& info = nextLine.Characters[nextLine.Characters.Size - 1];
					x = info.pos.x + info.glyph.increment;
					height += line.Height;
					prevC = '\0';
					line = nextLine;
				}
			} else {
				int kerning = textStyle->Kerning.get(prevC, c);
				x += glyph.increment + kerning;
				prevC = c;
			}
		}
		size.Width = std::max(size.Width, line.Width);
		lines.add(line);
		size.Height = height + line.Height;

		uint32_t y = 0;
		for (auto& line : lines) {
			y += line.Ascent;
			for (auto& info : line.Characters)
				info.pos.y = (float)y;
			y += line.Descent;
		}

		valid = true;
	}

	void TextLayout::initMeshes(
		ITextMeshFactory& textMeshFactory,
		ITextureFactory& textureFactory,
		NotNull<Material> material
	) {
		textMeshes.clear();
		material->addReference();
		this->textMaterial.set(material.get());
		for (auto& line : lines) {
			for (auto& span : line.Spans) {
				auto mesh = IntrusivePointer<Resource>(textMeshFactory.makeMesh(line.Characters, span));
				// TODO: support multiple materials
				TextureParameter* colorTextureParameter = (TextureParameter*)material->Parameters.get("colorTexture");
				colorTextureParameter->Value = IntrusivePointer<ITexture>(textureFactory.makeTexture(*span.textStyle->Atlas->Image)).get();
				textMeshes.add(mesh);
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

	void TextLayout::draw(RenderGroup& group, const XMFLOAT2& position) {
		if (!valid)
			refresh();
		auto material = IntrusivePointer<Material>(textMaterial->clone());
		Float2Parameter* positionParameter = (Float2Parameter*)material->Parameters.get("position");
		positionParameter->Value = position;
		for (auto& mesh : textMeshes) {
			group.objects.add({
				mesh,
				material,
				{ position.x, position.y, 0 }
			});
		}
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
