#pragma once

#include "Light.h"

#include <engine/3d/scene/transform/TransformComponent3D.h>

namespace Ghurund::Engine::_3D {
	class LightComponent3D {
	private:
		Light* light;

	public:
		LightComponent3D() {
			light = ghnew Ghurund::Engine::_3D::Light();
		}

		~LightComponent3D() {
			if (light)
				light->release();
		}

		inline Light* getLight() const {
			return light;
		}

		inline void setLight(Light* light) {
			setPointer(this->light, light);
		}

		__declspec(property(get = getLight, put = setLight)) Light* Light;

		inline void update(const TransformComponent3D& transform) {
			auto w = XMLoadFloat4x4(&transform.WorldTransformation);
			XMFLOAT3 pos;
			XMStoreFloat3(&pos, XMVector3TransformCoord(XMVectorZero(), w));
		}
	};
}
