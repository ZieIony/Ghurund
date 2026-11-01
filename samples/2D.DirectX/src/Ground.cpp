#include "Ground.h"

#include <engine/2d/scene/tiles/TileMap.h>
#include <engine/2d/scene/tiles/TileMapComponent.h>
#include <engine/2d/scene/transform/TransformComponent2D.h>
#include <engine/2d/physics/RigidBodyComponent2D.h>
#include <engine/2d/physics/visualization/VisualizationComponent2D.h>
#include <engine/2d/graphics/sprite/SpriteComponent.h>

namespace Sample {
	using namespace Ghurund::Engine::_2D;

	CoroutineTask<void> Ground::init(PhysicsSystem2D& physicsSystem, IGraphicsResourceFactory& resourceFactory, ResourceManager& resourceManager, IGPUMemoryManager& memoryManager) {
		addComponent<TransformComponent2D>();
		addComponent<SpriteComponent>();

		{
			auto& groundBox = addComponent<RigidBodyComponent2D>();
			groundBox.init(physicsSystem, ShapeType::BOX);
			groundBox.BodyType = BodyType::STATIC;
			groundBox.Size = { 5, 3 };
			auto& visComponent = addComponent<VisualizationComponent2D>();
			visComponent.init(memoryManager, groundBox);
		}

		{
			auto& tileMapComponent = addComponent<TileMapComponent>();
			auto tileMap = co_await resourceManager.load<TileMap>(ResourceManager::ENGINE_LIB_PATH / FilePath(L"test/images/terrainTileMap.xml"));
			tileMapComponent.TileMap = tileMap.get();
			tileMapComponent.init(resourceFactory, memoryManager);
		}
	}
}
