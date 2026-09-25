#include "ghe2dpch.h"
#include "TileMapComponent.h"

#include "core/application/Application.h"
#include "engine/2d/graphics/mesh/TileMapMeshData.h"
#include "engine/2d/Graphics2DFeature.h"
#include "engine/graphics/GraphicsFeature.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& TileMapComponent::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<TileMapComponent>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	CoroutineTask<void> TileMapComponent::onInit() {
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
		GraphicsFeature* graphicsFeature = Owner.World.app.Features.get<GraphicsFeature>();
		mesh = graphicsFeature->ResourceFactory.makeMesh(tileMapMeshData.ref());

		// TODO: clone materials in a more transparent way
		Material = Owner.World.app.ResourceManager.get<Ghurund::Engine::Material>(Graphics2DFeature::MATERIAL_SPRITE)->clone();

		co_return;
	}

	void TileMapComponent::reloadResource() {
		if (tileMap && !tileMap->IsValid) {
			uninit();
		} else {
			Owner.World.app.CoroutineScheduler.launch(init());
		}
	}
	
	void TileMapComponent::queueDraw(RenderGroup& group) {
		if (mesh && material) {
			auto w = XMLoadFloat4x4(&Owner.Transform.WorldTransformation);
			XMFLOAT4X4 world;
			XMStoreFloat4x4(&world, XMMatrixTranspose(w));

			inputs.Transformation = world;
			group.objects.add(DrawPacket(mesh, material, drawOrder));
		}
	}
}
