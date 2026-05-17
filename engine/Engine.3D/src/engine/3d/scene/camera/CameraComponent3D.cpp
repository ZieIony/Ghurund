#include "ghe3dpch.h"
#include "CameraComponent3D.h"

#include "engine/3d/scene/Entity3D.h"

namespace Ghurund::Engine::_3D {
	const Ghurund::Core::Type& CameraComponent3D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<CameraComponent3D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
		
	void CameraComponent3D::update(const Timer& timer) {
		auto w = XMLoadFloat4x4(&Owner->Transform.WorldTransformation);
		XMFLOAT3 pos;
		XMStoreFloat3(&pos, XMVector3TransformCoord(XMVectorZero(), w));
		XMFLOAT3 dir = { 0, 0, 1 };
		XMStoreFloat3(&dir, XMVector3TransformNormal(XMLoadFloat3(&dir), w));
		float dist = 1;

		camera->setPositionDirectionDistanceUp(pos, dir, dist);
		//camera->Roll = rotation;

		camera->update();
	}
}
