#pragma once

#include "engine/ecs/System.h"

namespace Ghurund::Engine {
	class World;
}

namespace Ghurund::Engine::_2D {
	class TransformSystem2D:public System {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = TransformSystem2D::GET_TYPE();
#pragma endregion

    private:
		World& world;

	public:
		TransformSystem2D(World& world):world(world) {}

		virtual void update(const Timer& timer);
	};
}
