#pragma once

#include "engine/ecs/System.h"

namespace Ghurund::Engine::_3D {
	class LightSystem3D:public System {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = LightSystem3D::GET_TYPE();
#pragma endregion

    private:
		class World3D& world;

	public:
		LightSystem3D(World3D& world):world(world) {}

		virtual void update(const Timer& timer);
	};
}
