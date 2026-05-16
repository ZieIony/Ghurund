#include "ghe2dpch.h"
#include "BodyComponent2D.h"

#include "engine/2d/physics/PhysicsSystem2D.h"
#include "engine/2d/World2D.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& BodyComponent2D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<BodyComponent2D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	CoroutineTask<void> BodyComponent2D::onInit() {
		b2BodyDef bodyDef = b2DefaultBodyDef();
		bodyDef.position = { 0.0f, 0.0f };
		id = b2CreateBody(physicsSystem.Id, &bodyDef);
		co_return;
	}

	BodyComponent2D::BodyComponent2D(NotNull<Entity2D> owner, World2D& world):Component2D(owner, world), physicsSystem(world.PhysicsSystem) {}

	void BodyComponent2D::fixedUpdate(const Timer& timer) {
		if (BodyType != BodyType::STATIC) {
			auto& transform = Owner->Transform;
			transform.Position = Position;
			transform.Rotation = Rotation;
		}
	}
}
