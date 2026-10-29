#include "ghe2dpch.h"
#include "SpriteAnimationSystem.h"

#include "AnimatedSpriteComponent.h"

#include "engine/ecs/World.h"
#include "engine/2d/graphics/sprite/SpriteComponent.h"

namespace Ghurund::Engine::_2D {
    void SpriteAnimationSystem::update(const Timer& timer) {
        auto view = world.entityRegistry.view<SpriteComponent, AnimatedSpriteComponent>();
        for (auto [id, sprite, animation] : view.each()) {
            animation.update(timer);
            sprite.ColorTexture = animation.Animation->CurrentTexture;
        };
    }
}
