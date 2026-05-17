#pragma once

#include "Camera3D.h"

#include "engine/3d/scene/component/Component3D.h"

namespace Ghurund::Engine::_3D {
	class CameraComponent3D:public Component3D {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = CameraComponent3D::GET_TYPE();
#pragma endregion

	private:
		Camera3D* camera;

	public:
		CameraComponent3D(NotNull<Entity3D> owner, World3D& world):Component3D(owner, world) {
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

		virtual void update(const Timer& timer) override;
	};
}