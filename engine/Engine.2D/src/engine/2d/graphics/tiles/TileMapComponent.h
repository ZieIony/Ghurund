#pragma once

#include "TileMap.h"

#include "engine/resource/IGraphicsResourceFactory.h"
#include "engine/graphics/material/Material.h"

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;
	using namespace ::DirectX;

	class TileMapComponent {
	private:
		TileMap* tileMap = nullptr;
		EventHandler<Resource, void, ResourceState> tileMapChanged = [this](Resource& resource, const ResourceState& prevState)->bool {
			reloadResource();
			return true;
		};

		Mesh* mesh = nullptr;

		void reloadResource();

	public:
		~TileMapComponent() {
			deinit();
		}

		void init(IGraphicsResourceFactory& resourceFactory);

		void deinit() {
			safeRelease(mesh);
			safeRelease(tileMap);
		};

		inline TileMap* getTileMap() {
			return tileMap;
		}

		inline void setTileMap(TileMap* tileMap) {
			if (this->tileMap)
				this->tileMap->stateChanged -= tileMapChanged;
			setPointer(this->tileMap, tileMap);
			if (tileMap)
				tileMap->stateChanged += tileMapChanged;
		}

		__declspec(property(get = getTileMap, put = setTileMap)) TileMap* TileMap;

		inline Mesh* getMesh() const {
			return mesh;
		}

		__declspec(property(get = getMesh)) Mesh* Mesh;
	};
}
