#pragma once

#include "core/math/Size.h"
#include "core/object/NotNull.h"
#include "core/resource/Resource.h"
#include "engine/graphics/texture/TextureAtlas.h"

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;
	using namespace ::DirectX;

	struct Tile {
		size_t index;
	};


	class TileSet:public Resource {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<TileSet>()
				.withSupertype(__super::GET_TYPE());

			return TYPE;
		}

		inline static const Ghurund::Core::Type& TYPE = TileSet::GET_TYPE();
#pragma endregion

	private:
		TextureAtlas* atlas = nullptr;
		Array<Tile> tiles;

	public:
		~TileSet() {
			if (atlas)
				atlas->release();
		}

		void init(NotNull<ITexture> texture, IntSize tileSize);

		void init(NotNull<ITexture> texture, XMUINT2 gridCount);

		inline const Tile& get(size_t index) const {
			return tiles[index];
		}

		inline void set(size_t index, size_t textureIndex) {
			tiles[index].index = textureIndex;
		}

		inline TextureAtlas* getTextureAtlas() {
			return atlas;
		}

		inline void setTextureAtlas(TextureAtlas* atlas) {
			setPointer(this->atlas, atlas);
		}

		__declspec(property(get = getTextureAtlas)) TextureAtlas* TextureAtlas;

		inline size_t getSize() const {
			return tiles.Size;
		}

		__declspec(property(get = getSize)) size_t Size;

#pragma region formats
	protected:
		virtual const Array<ResourceFormat>& getFormatsImpl() const override {
			return TileSet::FORMATS;
		}

	public:
		static const inline ResourceFormat FORMAT_XML = ResourceFormat(L"xml", ResourceFormatOptions::CAN_LOAD | ResourceFormatOptions::CAN_SAVE);

		inline static const Array<ResourceFormat>& FORMATS = { FORMAT_XML };

		static const inline uint32_t VERSION = 1;
#pragma endregion
	};
}