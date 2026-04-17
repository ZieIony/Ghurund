#pragma once

#include "engine/2d/scene/Entity2D.h"
#include <engine/2d/physics/component/BoxComponent2D.h>
#include <engine/2d/physics/component/SegmentComponent2D.h>
#include <engine/2d/scene/tiles/TileMap.h>
#include <engine/2d/scene/tiles/TileMapComponent.h>
#include "engine/2d/World2D.h"

namespace Demo {
	using namespace Ghurund::Engine::_2D;

	class Ground:public Entity2D {
	private:
		IntrusivePointer<BoxComponent2D> groundBox;
		IntrusivePointer<SegmentComponent2D> segmentBox;
		IntrusivePointer<TileMapComponent> tileMapComponent;
		IntrusivePointer<TileMap> tileMap;

	protected:
		virtual CoroutineTask<void> onInit() override {
			{
				groundBox = IntrusivePointer(makeComponent<BoxComponent2D>());
				co_await groundBox->init();
				groundBox->Type = BodyType::STATIC;
				groundBox->Position = { 0, 0 };
				groundBox->Size = { 5, 1 };
				RootComponent = groundBox.get();
			}

			{
				segmentBox = IntrusivePointer(makeComponent<SegmentComponent2D>());
				co_await segmentBox->init();
				segmentBox->Type = BodyType::STATIC;
				segmentBox->Position = { 0, -0.1f };
				segmentBox->Size = { 12, 1 };
				RootComponent->Components.add(segmentBox.get());
			}

			{
				tileMapComponent = IntrusivePointer(makeComponent<TileMapComponent>());
				tileMap = co_await World.app->ResourceManager.load<TileMap>(ResourceManager::ENGINE_LIB / FilePath(L"test/images/terrainTileMap.xml"));
				tileMapComponent->TileMap = tileMap.get();
				co_await tileMapComponent->init();
				tileMapComponent->Position = { 0.0f, -1.0f };
				RootComponent->Components.add(tileMapComponent.get());
			}
		}

	public:
		Ground(World2D& world):Entity2D(world) {}
	};
}
