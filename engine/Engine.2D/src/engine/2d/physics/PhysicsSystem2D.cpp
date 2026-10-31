#include "ghe2dpch.h"

#include "PhysicsSystem2D.h"

#include "engine/ecs/World.h"
#include <engine/2d/scene/transform/TransformComponent2D.h>
#include <engine/2d/physics/RigidBodyComponent2D.h>

#include <entt.hpp>

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& PhysicsSystem2D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<PhysicsSystem2D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void PhysicsSystem2D::fixedUpdate(const Timer& timer) {
		b2World_Step(id, timer.FixedFrameTime, subStepCount);
	}

	void PhysicsSystem2D::update(const Timer& timer) {
		if (timer.TimeScale == 0.0f)
			return;
		auto view = world.entityRegistry.view<TransformComponent2D, const RigidBodyComponent2D>();
		for (auto [id, transform, rigidBody] : view.each()) {
			rigidBody.update(timer, transform);
		};
	}
}
