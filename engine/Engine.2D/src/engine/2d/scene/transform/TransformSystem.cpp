#include "ghe2dpch.h"
#include "TransformSystem.h"

#include "engine/ecs/World.h"
#include "engine/2d/scene/transform/TransformComponent2D.h"

namespace Ghurund::Engine::_2D {
	void TransformSystem2D::update(const Timer& timer) {
		auto view = world.entityRegistry.view<TransformComponent2D>();
		view.each([](entt::entity id, TransformComponent2D& transform) {
			transform.update();
		});
	}
}
