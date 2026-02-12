#include "ghe2dpch.h"
#include "CameraComponent2D.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& CameraComponent2D::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<CameraComponent2D>();

		static const Ghurund::Core::Type TYPE = TypeBuilder<CameraComponent2D>()
			.withConstructor(CONSTRUCTOR)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
		
	void CameraComponent2D::update(const XMFLOAT4X4& parentTransformation, uint64_t time) {
		__super::update(parentTransformation, time);

		auto w = XMLoadFloat4x4(&worldTransformation);
		XMFLOAT3 pos;
		XMStoreFloat3(&pos, XMVector3TransformCoord(XMVectorZero(), w));

		camera->setPositionUp({ pos.x, pos.y });
		//camera->Roll = rotation;

		camera->update();
	}
}
