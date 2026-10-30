#pragma once

#include "engine/ecs/System.h"
#include "engine/2d/World2D.h"

namespace Ghurund::Engine::_2D {
	class CameraSystem2D:public System {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = CameraSystem2D::GET_TYPE();
#pragma endregion

	private:
		World2D& world;

	protected:
		virtual const Array<std::reference_wrapper<const Ghurund::Core::Type>>& getDependencies_internal() const override;

	public:
		CameraSystem2D(World2D& world):world(world) {}

		virtual void update(const Timer& timer) override;
	};
}
