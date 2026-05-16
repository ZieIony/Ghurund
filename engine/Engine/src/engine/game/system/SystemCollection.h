#pragma once

#include "System.h"

#include "engine/game/GameObjectUpdateCollection.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class SystemCollection {
    private:
        GameObjectUpdateCollection& gameObjects;
        List<IntrusivePointer<System>> systems;

    public:
        SystemCollection(GameObjectUpdateCollection& gameObjects):gameObjects(gameObjects) {}

        inline void add(IntrusivePointer<System> system) {
            systems.add(system);
        }

        inline void remove(IntrusivePointer<System> system) {
            systems.remove(system);
        }

        inline void init() {
            for (auto& system : systems) {
                system->init();
                gameObjects.add(system);
            }
        }

        inline void uninit() {
            for (auto& system : systems) {
                gameObjects.remove(system);
                system->uninit();
            }
        }
    };
}
