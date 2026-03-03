#include "ghe2dpch.h"
#include "TileSet.h"

namespace Ghurund::Engine::_2D {
	void TileSet::init(NotNull<ITexture> texture, IntSize tileSize) {
		auto atlas = makeIntrusive<Ghurund::Engine::TextureAtlas>();
		atlas->init(texture, tileSize);
		setPointer(this->atlas, atlas.get());

		uint32_t tileCount = texture->Size.Width / tileSize.Width * texture->Size.Height / tileSize.Height;
		tiles = Array<Tile>(tileCount);
		for (size_t i = 0; i < tileCount; i++)
			tiles[i].index = i;
	}

	void TileSet::init(NotNull<ITexture> texture, XMUINT2 gridSize) {
		auto atlas = makeIntrusive<Ghurund::Engine::TextureAtlas>();
		atlas->init(texture, gridSize);

		uint32_t tileCount = gridSize.x * gridSize.y;
		tiles = Array<Tile>(tileCount);
		for (size_t i = 0; i < tileCount; i++)
			tiles[i].index = i;
	}
}
