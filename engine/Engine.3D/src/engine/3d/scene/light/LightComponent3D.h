#pragma once

#include "Light.h"

#include "engine/3d/scene/component/Component3D.h"

namespace Ghurund::Engine::_3D {
	class LightComponent3D:public Component3D {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = LightComponent3D::GET_TYPE();
#pragma endregion

	private:
		Light* light;

	public:
		LightComponent3D(NotNull<Entity3D> owner, World3D& world):Component3D(owner, world) {
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

		virtual void update(const Timer& timer) override;
	};
}
