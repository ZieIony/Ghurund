#include "ghe3dpch.h"
#include "LightComponent3D.h"

#include "engine/3d/scene/Entity3D.h"

namespace Ghurund::Engine::_3D {
	const Ghurund::Core::Type& LightComponent3D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<LightComponent3D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
		
	void LightComponent3D::update(const Timer& timer) {
		auto w = XMLoadFloat4x4(&Owner->Transform.WorldTransformation);
		XMFLOAT3 pos;
		XMStoreFloat3(&pos, XMVector3TransformCoord(XMVectorZero(), w));

		//camera->setPositionUp({ pos.x, pos.y });
		//camera->Roll = rotation;

		//camera->update();
	}
}
