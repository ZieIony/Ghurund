#pragma once

#include "TileMap.h"

#include "engine/2d/graphics/sprite/SpriteComponent.h"
#include "engine/resource/IGraphicsResourceFactory.h"

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
		Material* material = nullptr;

		void reloadResource();

	public:
		~TileMapComponent() {
			deinit();
		}

		CoroutineTask<void> init(IGraphicsResourceFactory& resourceFactory, ResourceManager& resourceManager);

		void deinit() {
			safeRelease(mesh);
			safeRelease(material);
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

		inline Material* getMaterial() const {
			return material;
		}

		inline void setMaterial(Material* material) {
			setPointer(this->material, material);
		}

		__declspec(property(get = getMaterial, put = setMaterial)) Material* Material;

		inline Mesh* getMesh() const {
			return mesh;
		}

		__declspec(property(get = getMesh)) Mesh* Mesh;
	};
}
