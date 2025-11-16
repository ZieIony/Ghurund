#include "ghepch.h"
#include "TextMesh.h"

namespace Ghurund::Engine {
	void TextMesh::init(const WString& text, const Ghurund::UI::Font& font) {
		List<XMFLOAT3> positions;
		List<XMFLOAT2> texCoords;
		List<uint16_t> indices;

		auto imageSize = font.Atlas->Image->Size;
		auto& glyphs = font.Atlas->Glyphs;
		float x = 0;
		tchar prevC = '\0';
		for (wchar_t c : text) {
			if (!glyphs.contains(c)) {
				Logger::log(LogType::WARNING, std::format(_T("Font doesn't contain glyph definition for character '{}'.\n"), c).c_str());
				continue;
			}
			auto& glyph = glyphs[c];
			float nextX = x + glyph.width;
			if (isSpace(c)) {
				prevC = c;
				x = nextX;
				continue;
			}
			indices.addAll({
				(uint16_t)positions.Size, (uint16_t)(positions.Size + 1), (uint16_t)(positions.Size + 2),
				(uint16_t)(positions.Size + 2), (uint16_t)(positions.Size + 1), (uint16_t)(positions.Size + 3)
				});
			float PAD = 8 / 2;	// TODO: this should be Font::MAX_DIST
			float PAD_S = PAD / glyph.scale;
			int kerning = font.getKerning(prevC, c);
			positions.addAll({
				{
					x - PAD_S - glyph.shapeOrigin.x,
					-PAD_S - glyph.shapeOrigin.y,
					0.0f
				},
				{
					x - PAD_S - glyph.shapeOrigin.x,
					(float)(glyph.shapeSize.Height + PAD_S - glyph.shapeOrigin.y),
					0.0f
				},
				{
					x + glyph.shapeSize.Width + PAD_S - glyph.shapeOrigin.x,
					-PAD_S - glyph.shapeOrigin.y,
					0.0f
				},
				{
					x + glyph.shapeSize.Width + PAD_S - glyph.shapeOrigin.x,
					(float)(glyph.shapeSize.Height + PAD_S - glyph.shapeOrigin.y),
					0.0f
				}
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
			prevC = c;
			x = nextX + kerning;
		}
		VertexStream posStream = VertexStream(positions, VertexRole::POSITION);
		VertexStream texCoordStream = VertexStream(texCoords, VertexRole::TEXCOORD);

		MeshData::init({ posStream, texCoordStream }, positions.Size, indices);
	}
}