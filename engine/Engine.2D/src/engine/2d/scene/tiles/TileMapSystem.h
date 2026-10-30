#pragma once

#include "engine/ecs/System.h"
#include "engine/2d/graphics/sprite/SpriteRenderingSystem.h"

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

    protected:
        virtual const Array<std::reference_wrapper<const Ghurund::Core::Type>>& getDependents_internal() const override {
            static Array<std::reference_wrapper<const Ghurund::Core::Type>> dependents = { SpriteRenderingSystem::TYPE };
            return dependents;
        }

    public:
        TileMapSystem(World& world):world(world) {
        }

        virtual void update(const Timer& timer) override;
    };
}
