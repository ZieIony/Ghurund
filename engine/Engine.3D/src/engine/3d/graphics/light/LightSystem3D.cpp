#include "ghe3dpch.h"
#include "LightSystem3D.h"

#include "engine/ecs/World.h"
#include "engine/3d/graphics/light/LightComponent3D.h"

namespace Ghurund::Engine::_3D {
	const Ghurund::Core::Type& LightSystem3D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<LightSystem3D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void LightSystem3D::update(const Timer& timer) {
		auto view = world.entityRegistry.view<LightComponent3D, TransformComponent3D>();
		view.each([](entt::entity id, LightComponent3D& light, const TransformComponent3D& transform) {
			light.update(transform);
		});
	}
}
