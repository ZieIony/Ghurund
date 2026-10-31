#include "ghe3dpch.h"
#include "TransformSystem3D.h"

#include "engine/ecs/World.h"
#include "engine/3d/scene/transform/TransformComponent3D.h"

namespace Ghurund::Engine::_3D {
	const Ghurund::Core::Type& TransformSystem3D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<TransformSystem3D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void TransformSystem3D::update(const Timer& timer) {
		auto view = world.entityRegistry.view<TransformComponent3D>();
		view.each([](entt::entity id, TransformComponent3D& transform) {
			transform.update();
		});
	}
}
