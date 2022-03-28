#pragma once

#include "CameraComponent.h"
#include "entity/Entity.h"

namespace Ghurund {
    class CameraEntity:public Entity {
    public:
        CameraEntity(entt::registry& registry):Entity(registry) {
            Components.add<CameraComponent>();
            Name = L"camera";
        }
    };
}