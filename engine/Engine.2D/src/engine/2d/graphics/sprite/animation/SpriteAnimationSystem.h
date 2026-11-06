#pragma once

#include "engine/ecs/System.h"

namespace Ghurund::Engine::_2D {
    class SpriteAnimationSystem:public System {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = SpriteAnimationSystem::GET_TYPE();
#pragma endregion

    private:
        class World2D& world;

    public:
        SpriteAnimationSystem(World2D& world):world(world) {}

        virtual void update(const Timer& timer) override;
    };
}