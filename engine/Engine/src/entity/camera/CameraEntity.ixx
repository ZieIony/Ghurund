module;

#include <entt.hpp>

export module Ghurund.Engine.Entity.Camera.CameraEntity;

import Ghurund.Engine.Entity.Camera.CameraComponent;
import Ghurund.Engine.Entity.Entity;

export namespace Ghurund {
    class CameraEntity:public Entity {
    public:
        CameraEntity(entt::registry& registry):Entity(registry) {
            Components.add<CameraComponent>();
            Name = L"camera";
        }
    };
}