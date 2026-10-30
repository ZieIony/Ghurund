#include "ghe2dpch.h"
#include "CameraSystem2D.h"

#include "CameraComponent2D.h"
#include "engine/2d/scene/transform/TransformComponent2D.h"
#include "engine/2d/scene/transform/TransformSystem2D.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& CameraSystem2D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<CameraSystem2D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	const Array<std::reference_wrapper<const Ghurund::Core::Type>>& CameraSystem2D::getDependencies_internal() const {
		static Array<std::reference_wrapper<const Ghurund::Core::Type>> dependencies = { TransformSystem2D::TYPE };
		return dependencies;
	}
	
	void CameraSystem2D::update(const Timer& timer) {
		auto view = world.entityRegistry.view<TransformComponent2D, CameraComponent2D>();
		view.each([](const auto& id, const auto& transform, auto& camera) {
			camera.update(transform);
		});
	}
}
