#include "ghe3dpch.h"
#include "CameraSystem3D.h"

#include "CameraComponent3D.h"
#include "engine/3d/scene/transform/TransformComponent3D.h"
#include "engine/3d/scene/transform/TransformSystem3D.h"

namespace Ghurund::Engine::_3D {
	const Ghurund::Core::Type& CameraSystem3D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<CameraSystem3D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	const Array<std::reference_wrapper<const Ghurund::Core::Type>>& CameraSystem3D::getDependencies_internal() const {
		static Array<std::reference_wrapper<const Ghurund::Core::Type>> dependencies = { TransformSystem3D::TYPE };
		return dependencies;
	}
	
	void CameraSystem3D::update(const Timer& timer) {
		auto view = world.entityRegistry.view<TransformComponent3D, CameraComponent3D>();
		view.each([](const auto& id, const auto& transform, auto& camera) {
			camera.update(transform);
		});
	}
}
