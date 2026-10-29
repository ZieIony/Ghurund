#pragma once

#include "engine/2d/scene/camera/Camera2D.h"
#include "engine/ecs/System.h"
#include "engine/parameter/ValueParameter.h"

namespace Ghurund::Engine {
    class World;
}

namespace Ghurund::Engine::_2D {
    class SpriteAnimationSystem:public System {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<SpriteAnimationSystem>()
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        inline static const Ghurund::Core::Type& TYPE = SpriteAnimationSystem::GET_TYPE();
#pragma endregion

    private:
        World& world;

    public:
        SpriteAnimationSystem(World& world):world(world) {}

        virtual void update(const Timer& timer) override;
    };
}