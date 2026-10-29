#pragma once

#include "Camera2D.h"

#include <engine/2d/scene/transform/TransformComponent2D.h>

namespace Ghurund::Engine::_2D {
	class CameraComponent2D {
	private:
		Camera2D* camera;

	public:
		CameraComponent2D() {
			camera = ghnew Camera2D();
		}

		~CameraComponent2D() {
			if (camera)
				camera->release();
		}

		inline Camera2D* getCamera() const {
			return camera;
		}

		inline void setCamera(Camera2D* camera) {
			setPointer(this->camera, camera);
		}

		__declspec(property(get = getCamera, put = setCamera)) Camera2D* Camera;

		inline void update(const TransformComponent2D& transform) {
			auto w = XMLoadFloat4x4(&transform.WorldTransformation);
			XMFLOAT3 pos;
			XMStoreFloat3(&pos, XMVector3TransformCoord(XMVectorZero(), w));

			camera->setPositionUp({ pos.x, pos.y });
			camera->update();
		}
	};
}
