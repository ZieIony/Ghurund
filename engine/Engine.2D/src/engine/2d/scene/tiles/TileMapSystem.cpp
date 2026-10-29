#include "ghe2dpch.h"
#include "TileMapSystem.h"

#include "TileMapComponent.h"

#include "engine/ecs/World.h"
#include "engine/2d/graphics/sprite/SpriteComponent.h"

namespace Ghurund::Engine::_2D {
    void TileMapSystem::update(const Timer& timer) {
        auto view = world.entityRegistry.view<SpriteComponent, TileMapComponent>();
        for (auto [id, sprite, tileMapComponent] : view.each()) {
            sprite.Material = tileMapComponent.Material;
            sprite.Mesh = tileMapComponent.Mesh;
            sprite.ColorTexture = tileMapComponent.TileMap->TileSet->TextureAtlas->get();
        };
    }
}
