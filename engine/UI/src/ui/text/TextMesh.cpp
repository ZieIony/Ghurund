#include "ghuipch.h"
#include "TextMesh.h"

namespace Ghurund::UI {
	using namespace Ghurund::Engine;

	void TextMesh::init(const List<CharacterInfo>& characters, const TextSpan& span) {
		List<XMFLOAT3> positions;
		List<XMFLOAT2> texCoords;
		List<uint16_t> indices;

		const Ghurund::UI::Font& font = *span.font;

		auto imageSize = font.Atlas->Image->Size;
		auto& glyphs = font.Atlas->Glyphs;
		tchar prevC = '\0';
		for (size_t i = span.start; i < span.finish; i++) {
			CharacterInfo& info = characters[i];
			if (isSpace(info.c))
				continue;
			indices.addAll({
				(uint16_t)positions.Size, (uint16_t)(positions.Size + 1), (uint16_t)(positions.Size + 2),
				(uint16_t)(positions.Size + 2), (uint16_t)(positions.Size + 1), (uint16_t)(positions.Size + 3)
				});
			auto& glyph = info.glyph;
			float PAD = font.Atlas->Padding / 2;
			float PAD_S = PAD / glyph.scale;
			int kerning = font.getKerning(prevC, info.c);
			FloatSize frameSize = { glyph.shapeSize.Width + PAD_S * 2, glyph.shapeSize.Height + PAD_S * 2 };
			XMFLOAT2 framePos = { info.pos.x - PAD_S + glyph.shapeOrigin.x, info.pos.y - PAD_S - glyph.shapeOrigin.y };
			positions.addAll({
				{ framePos.x, framePos.y, 0.0f },
				{ framePos.x, framePos.y + frameSize.Height, 0.0f },
				{ framePos.x + frameSize.Width, framePos.y, 0.0f },
				{ framePos.x + frameSize.Width, framePos.y + frameSize.Height, 0.0f },
				});
			texCoords.addAll({
				{
					(float)(glyph.bitmapPos.x + PAD) / imageSize.Width,
					(float)(glyph.bitmapPos.y + PAD) / imageSize.Height
				},
				{
					(float)(glyph.bitmapPos.x + PAD) / imageSize.Width,
					(float)(glyph.bitmapPos.y - PAD + glyph.bitmapSize.Height) / imageSize.Height
				},
				{
					(float)(glyph.bitmapPos.x - PAD + glyph.bitmapSize.Width) / imageSize.Width,
					(float)(glyph.bitmapPos.y + PAD) / imageSize.Height
				},
				{
					(float)(glyph.bitmapPos.x - PAD + glyph.bitmapSize.Width) / imageSize.Width,
					(float)(glyph.bitmapPos.y - PAD + glyph.bitmapSize.Height) / imageSize.Height
				}
				});
			prevC = info.c;
		}
		VertexStream posStream = VertexStream(positions, VertexRole::POSITION);
		VertexStream texCoordStream = VertexStream(texCoords, VertexRole::TEXCOORD);

		MeshData::init({ posStream, texCoordStream }, positions.Size, indices);
	}
}