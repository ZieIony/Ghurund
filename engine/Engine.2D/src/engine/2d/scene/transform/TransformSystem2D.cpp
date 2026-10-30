#include "ghe2dpch.h"
#include "TransformSystem2D.h"

#include "engine/ecs/World.h"
#include "engine/2d/scene/transform/TransformComponent2D.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& TransformSystem2D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<TransformSystem2D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void TransformSystem2D::update(const Timer& timer) {
		auto view = world.entityRegistry.view<TransformComponent2D>();
		view.each([](entt::entity id, TransformComponent2D& transform) {
			transform.update();
		});
	}
}
