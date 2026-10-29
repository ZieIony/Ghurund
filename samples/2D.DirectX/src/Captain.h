#pragma once

#include "engine/ecs/Entity.h"
#include <core/coroutine/CoroutineTask.h>
#include <engine/2d/audio/component/AudioListenerComponent2D.h>
#include <engine/2d/audio/component/SoundComponent2D.h>
#include <engine/2d/scene/transform/TransformComponent2D.h>
#include <engine/2d/World2D.h>
#include <engine/2d/graphics/sprite/animation/AnimatedSpriteComponent.h>
#include <engine/2d/physics/RigidBodyComponent2D.h>

namespace Sample {
	using namespace Ghurund::Core;
	using namespace Ghurund::Engine;
	using namespace Ghurund::Engine::_2D;

	class Captain:public Entity {
	public:
		Captain() {}

		Captain(entt::registry& registry, entt::entity id):Entity(registry, id) {}

		CoroutineTask<void> init(PhysicsSystem2D& physicsSystem, ResourceManager& resourceManager, World2D& world);

		inline TransformComponent2D& getTransform() {
			return getComponent<TransformComponent2D>();
		}

		__declspec(property(get = getTransform)) TransformComponent2D& Transform;

		inline AnimatedSpriteComponent& getAnimatedSprite() {
			return getComponent<AnimatedSpriteComponent>();
		}

		__declspec(property(get = getAnimatedSprite)) AnimatedSpriteComponent& AnimatedSprite;

		inline RigidBodyComponent2D& getCapsuleComponent() {
			return getComponent<RigidBodyComponent2D>();
		}

		__declspec(property(get = getCapsuleComponent)) RigidBodyComponent2D& CapsuleComponent;

		inline void playSound() {
			getComponent<SoundComponent2D>().play();
		}

		inline void jump() {
			CapsuleComponent.applyForce({0, 100});
		}

		inline void moveLeft() {
			CapsuleComponent.applyForce({-50, 0});
			Transform.Scale = { -1, 1 };
		}

		inline void moveRight() {
			CapsuleComponent.applyForce({ 50, 0 });
			Transform.Scale = { 1, 1 };
		}

		void update(const Timer& timer);
	};
}
