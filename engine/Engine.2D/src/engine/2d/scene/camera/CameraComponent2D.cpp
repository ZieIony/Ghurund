#include "ghe2dpch.h"
#include "CameraComponent2D.h"

#include "engine/2d/scene/Entity2D.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& CameraComponent2D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<CameraComponent2D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
		
	void CameraComponent2D::update(const Timer& timer) {
		auto w = XMLoadFloat4x4(&Owner->Transform.WorldTransformation);
		XMFLOAT3 pos;
		XMStoreFloat3(&pos, XMVector3TransformCoord(XMVectorZero(), w));

		camera->setPositionUp({ pos.x, pos.y });
		//camera->Roll = rotation;

		camera->update();
	}
}
