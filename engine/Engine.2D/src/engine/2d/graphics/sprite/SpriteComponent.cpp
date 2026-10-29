#include "ghe2dpch.h"
#include "SpriteComponent.h"

#include "engine/2d/Graphics2DFeature.h"

namespace Ghurund::Engine::_2D {
	CoroutineTask<void> SpriteComponent::init(ResourceManager& resourceManager) {
		auto spriteMesh = co_await resourceManager.load<Ghurund::Engine::Mesh>(Graphics2DFeature::MESH_SPRITE);
		Mesh = spriteMesh.get();
		auto spriteMaterial = co_await resourceManager.load<Ghurund::Engine::Material>(
			Graphics2DFeature::MATERIAL_SPRITE,
			DirectoryPath::getCurrentDirectory(),
			ResourceFormat::AUTO,
			{ .clone = true }
		);
		Material = spriteMaterial.get();
	}
}
