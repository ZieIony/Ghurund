#pragma once

#include <entt.hpp>

#include "LightComponent.h"
#include "entity/Entity.h"

namespace Ghurund {
    class LightEntity:public Entity {
    public:
        LightEntity(entt::registry& registry):Entity(registry) {
            Components.add<LightComponent>();
            Name = L"light";
        }
    };
}