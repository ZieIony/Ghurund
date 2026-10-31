#pragma once

#include "Camera3D.h"

#include <engine/3d/scene/transform/TransformComponent3D.h>

namespace Ghurund::Engine::_3D {
	class CameraComponent3D {
	private:
		Camera3D* camera;

	public:
		CameraComponent3D() {
			camera = ghnew Camera3D();
		}

		~CameraComponent3D() {
			if (camera)
				camera->release();
		}

		inline Camera3D* getCamera() const {
			return camera;
		}

		inline void setCamera(Camera3D* camera) {
			setPointer(this->camera, camera);
		}

		__declspec(property(get = getCamera, put = setCamera)) Camera3D* Camera;

		inline void update(const TransformComponent3D& transform) {
			auto w = XMLoadFloat4x4(&transform.WorldTransformation);
			XMFLOAT3 pos;
			XMStoreFloat3(&pos, XMVector3TransformCoord(XMVectorZero(), w));
			XMFLOAT3 dir = { 0, 0, 1 };
			XMStoreFloat3(&dir, XMVector3TransformNormal(XMLoadFloat3(&dir), w));
			float dist = 1;

			//camera->setPositionDirectionDistanceUp(pos, dir, dist);
			camera->update();
		}
	};
}
