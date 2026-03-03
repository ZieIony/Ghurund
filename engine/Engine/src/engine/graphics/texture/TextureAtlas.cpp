#include "ghepch.h"
#include "TextureAtlas.h"

namespace Ghurund::Engine {
	void TextureAtlas::init(NotNull<ITexture> texture, IntSize singleSize) {
		setPointer(this->texture, texture.get());
		XMUINT2 gridSize = {
			(uint32_t)std::floorf((float)texture->Size.Width / singleSize.Width),
			(uint32_t)std::floorf((float)texture->Size.Height / singleSize.Height)
		};
		for (uint32_t y = 0; y < gridSize.y; y++) {
			for (uint32_t x = 0; x < gridSize.x; x++) {
				coordinates.add({
					(float)x * singleSize.Width / texture->Size.Width,
					(float)y * singleSize.Height / texture->Size.Height,
					(float)(x + 1) * singleSize.Width / texture->Size.Width,
					(float)(y + 1) * singleSize.Height / texture->Size.Height
				});
			}
		}
	}

	void TextureAtlas::init(NotNull<ITexture> texture, XMUINT2 gridSize) {
		setPointer(this->texture, texture.get());
		IntSize singleSize = {
			(uint32_t)std::floorf((float)texture->Size.Width / gridSize.x),
			(uint32_t)std::floorf((float)texture->Size.Height / gridSize.y)
		};
		for (uint32_t y = 0; y < gridSize.y; y++) {
			for (uint32_t x = 0; x < gridSize.x; x++) {
				coordinates.add({
					(float)x * singleSize.Width / texture->Size.Width,
					(float)y * singleSize.Height / texture->Size.Height,
					(float)(x + 1) * singleSize.Width / texture->Size.Width,
					(float)(y + 1) * singleSize.Height / texture->Size.Height
				});
			}
		}
	}
}
