#pragma once

#include "engine/ecs/System.h"

namespace Ghurund::Engine {
    class World;
}

namespace Ghurund::Engine::_2D {
    class TileMapSystem:public System {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<TileMapSystem>()
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        inline static const Ghurund::Core::Type& TYPE = TileMapSystem::GET_TYPE();
#pragma endregion

    private:
        World& world;

    public:
        TileMapSystem(World& world):world(world) {
        }

        virtual void update(const Timer& timer) override;
    };
}
