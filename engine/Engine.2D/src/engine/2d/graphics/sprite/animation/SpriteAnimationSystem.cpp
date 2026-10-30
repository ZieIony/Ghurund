#include "ghe2dpch.h"
#include "SpriteAnimationSystem.h"

#include "SpriteAnimationComponent.h"

#include "engine/ecs/World.h"
#include "engine/2d/graphics/sprite/SpriteComponent.h"

namespace Ghurund::Engine::_2D {
    const Ghurund::Core::Type& SpriteAnimationSystem::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<SpriteAnimationSystem>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void SpriteAnimationSystem::update(const Timer& timer) {
        auto view = world.entityRegistry.view<SpriteComponent, SpriteAnimationComponent>();
        for (auto [id, sprite, animation] : view.each()) {
            animation.update(timer);
            sprite.ColorTexture = animation.Animation->CurrentTexture;
        };
    }
}
