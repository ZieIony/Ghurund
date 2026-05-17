#include "ghe3dpch.h"
#include "TransformComponent3D.h"

namespace Ghurund::Engine::_3D {
	const Ghurund::Core::Type& TransformComponent3D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = Ghurund::Core::TypeBuilder<TransformComponent3D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void TransformComponent3D::update(const Timer& timer) {

		auto scaling = XMMatrixScaling(scale.x, scale.y, scale.z);
		auto rotation = XMMatrixRotationRollPitchYaw(this->rotation.y, this->rotation.x, this->rotation.z);
		auto translation = XMMatrixTranslation(position.x, position.y, position.z);
		auto local = scaling * rotation * translation;
		XMStoreFloat4x4(&localTransformation, local);

		XMStoreFloat4x4(&worldTransformation, local);// * XMLoadFloat4x4(&parentTransformation));

		__super::update(timer);
	}
}
