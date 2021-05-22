#pragma once

#include "LightComponent.h"
#include "game/entity/Entity.h"

namespace Ghurund {
    class LightEntity:public Entity {
    public:
        LightEntity(entt::registry& registry):Entity(registry) {
            Components.add<LightComponent>();
            Name = L"light";
        }
    };
}