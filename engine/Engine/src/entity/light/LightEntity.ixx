module;

#include <entt.hpp>

export module Ghurund.Engine.Entity.Light.LightEntity;

import Ghurund.Engine.Entity.Light.LightComponent;
import Ghurund.Engine.Entity.Entity;

export namespace Ghurund {
    class LightEntity:public Entity {
    public:
        LightEntity(entt::registry& registry):Entity(registry) {
            Components.add<LightComponent>();
            Name = L"light";
        }
    };
}