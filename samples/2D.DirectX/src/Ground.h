#pragma once

#include "core/coroutine/CoroutineTask.h"
#include "engine/2d/physics/PhysicsSystem2D.h"
#include "engine/ecs/Entity.h"
#include "engine/resource/IGraphicsResourceFactory.h"

namespace Sample {
	using namespace Ghurund::Core;
	using namespace Ghurund::Engine;
	using namespace Ghurund::Engine::_2D;

	class Ground:public Entity {
	public:
		Ground() {}

		Ground(entt::registry& registry, entt::entity id):Entity(registry, id) {}

		CoroutineTask<void> init(PhysicsSystem2D& physicsSystem, IGraphicsResourceFactory& resourceFactory, ResourceManager& resourceManager);
	};
}
