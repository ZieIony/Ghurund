#pragma once

#include "CameraComponent.h"
#include "game/entity/Entity.h"

namespace Ghurund {
    class CameraEntity:public Entity {
    public:
        CameraEntity(entt::registry& registry):Entity(registry) {
            Components.add<CameraComponent>();
            Name = L"camera";
        }
    };
}