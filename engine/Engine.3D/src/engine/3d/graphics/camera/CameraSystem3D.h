#pragma once

#include "engine/ecs/System.h"
#include "engine/3d/World3D.h"

namespace Ghurund::Engine::_3D {
	class CameraSystem3D:public System {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = CameraSystem3D::GET_TYPE();
#pragma endregion

	private:
		World3D& world;

	protected:
		virtual const Array<std::reference_wrapper<const Ghurund::Core::Type>>& getDependencies_internal() const override;

	public:
		CameraSystem3D(World3D& world):world(world) {}

		virtual void update(const Timer& timer) override;
	};
}
