#pragma once

#include "TileSet.h"

#include "core/math/Size.h"
#include "core/object/NotNull.h"

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;
	using namespace ::DirectX;

	class TileMap:public Resource {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<TileMap>()
				.withSupertype(__super::GET_TYPE());

			return TYPE;
		}

		inline static const Ghurund::Core::Type& TYPE = TileMap::GET_TYPE();
#pragma endregion

	private:
		TileSet* tileSet = nullptr;
		IntSize size;
		Array<uint16_t> tiles;

	public:
		~TileMap() {
			if (tileSet)
				tileSet->release();
		}

		void init(NotNull<TileSet> tileSet, IntSize size) {
			setPointer(this->tileSet, tileSet.get());
			this->size = size;
			tiles = Array<uint16_t>(size.Width * size.Height);
			dataSize.system = sizeof(*this) + sizeof(uint16_t) * tiles.Size;
			State = ResourceState::INITIALIZED;
		}

		void init(NotNull<TileSet> tileSet, IntSize size, const Array<uint16_t>& tiles) {
			setPointer(this->tileSet, tileSet.get());
			this->size = size;
			this->tiles = tiles;
			dataSize.system = sizeof(*this) + sizeof(uint16_t) * tiles.Size;
			State = ResourceState::INITIALIZED;
		}

		inline uint16_t get(XMUINT2 pos) const {
			_ASSERTE(pos.x < size.Width && pos.y < size.Height);
			return tiles.get(pos.y * size.Width + pos.x);
		}

		inline void set(XMUINT2 pos, uint16_t index) {
			tiles.get(pos.y * size.Width + pos.x) = index;
		}

		inline TileSet* getTileSet() {
			return tileSet;
		}

		inline void setTileSet(TileSet* tileSet) {
			setPointer(this->tileSet, tileSet);
		}

		__declspec(property(get = getTileSet)) TileSet* TileSet;

		inline const IntSize& getSize() const {
			return size;
		}

		__declspec(property(get = getSize)) const IntSize& Size;

#pragma region formats
	protected:
		virtual const Array<ResourceFormat>& getFormatsImpl() const override {
			return TileMap::FORMATS;
		}

	public:
		static const inline ResourceFormat FORMAT_XML = ResourceFormat(L"xml", ResourceFormatOptions::CAN_LOAD | ResourceFormatOptions::CAN_SAVE, 1);

		inline static const Array<ResourceFormat>& FORMATS = { FORMAT_XML };
#pragma endregion
	};
}