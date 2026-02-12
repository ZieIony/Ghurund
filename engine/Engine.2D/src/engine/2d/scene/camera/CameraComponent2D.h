#pragma once

#include "Camera2D.h"
#include "engine/2d/scene/component/TransformComponent2D.h"

namespace Ghurund::Engine::_2D {
	class CameraComponent2D:public TransformComponent2D {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = CameraComponent2D::GET_TYPE();
#pragma endregion

	private:
		Camera2D* camera;

	public:
		CameraComponent2D() {
			camera = ghnew Camera2D();
		}

		CameraComponent2D(NotNull<Camera2D> camera):camera(camera.get()) {
			camera->addReference();
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

		virtual void update(const XMFLOAT4X4& parentTransformation, uint64_t time) override;
	};
}