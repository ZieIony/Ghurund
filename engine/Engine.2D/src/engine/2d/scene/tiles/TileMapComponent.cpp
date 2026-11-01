#include "ghe2dpch.h"
#include "TileMapComponent.h"

#include "core/application/Application.h"
#include "engine/2d/scene/tiles/TileMapMeshData.h"
#include "engine/2d/Graphics2DFeature.h"

namespace Ghurund::Engine::_2D {
	void TileMapComponent::init(IGraphicsResourceFactory& resourceFactory, IGPUMemoryManager& memoryManager) {
		Array<TileInfo> tiles = tileMap->Size.Width * tileMap->Size.Height;
		uint32_t tileIndex = 0;
		for (TileInfo& tileInfo : tiles) {
			uint32_t x = tileIndex % tileMap->Size.Width;
			uint32_t y = tileIndex / tileMap->Size.Width;
			size_t tileSetIndex = tileMap->get({ x, y });
			auto tile = tileMap->TileSet->get(tileSetIndex);
			auto atlas = tileMap->TileSet->TextureAtlas;
			auto texCoords = atlas->get(tile.index);
			tileInfo.texCoordTopLeft = { texCoords.x, texCoords.y };
			tileInfo.texCoordBottomRight = { texCoords.z, texCoords.w };
			tileIndex++;
		}

		auto tileMapMeshData = makeIntrusive<TileMapMeshData>();
		tileMapMeshData->init(tileMap->Size, tiles);
		mesh = resourceFactory.makeMesh(tileMapMeshData.ref());

		auto spriteMaterial = IntrusivePointer<Ghurund::Engine::Material>(Graphics2DFeature::MATERIAL_SPRITE->clone());
		spriteMaterial->init(memoryManager);
		Material = spriteMaterial.get();
	}

	void TileMapComponent::reloadResource() {
		//Owner.World.app.ResourceManager.reload(*tileMap);
	}
}
