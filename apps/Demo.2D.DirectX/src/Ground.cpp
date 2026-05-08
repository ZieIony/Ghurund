#include "Ground.h"

#include "core/application/Application.h"
#include "engine/2d/World2D.h"

namespace Demo {
	CoroutineTask<void> Ground::onInit() {
		{
			groundBox = IntrusivePointer(makeComponent<BoxComponent2D>());
			co_await groundBox->init();
			groundBox->BodyType = BodyType::STATIC;
			groundBox->Size = { 5, 3 };
			Components.add(groundBox.get());
		}

		{
			segmentBox = IntrusivePointer(makeComponent<SegmentComponent2D>());
			co_await segmentBox->init();
			segmentBox->BodyType = BodyType::STATIC;
			segmentBox->Position = { 0, -0.1f };
			segmentBox->Width = 12;
			Components.add(segmentBox.get());
		}

		{
			tileMapComponent = IntrusivePointer(makeComponent<TileMapComponent>());
			tileMap = co_await World.app->ResourceManager.load<TileMap>(ResourceManager::ENGINE_LIB / FilePath(L"test/images/terrainTileMap.xml"));
			tileMapComponent->TileMap = tileMap.get();
			co_await tileMapComponent->init();
			Components.add(tileMapComponent.get());
		}
	}
}
