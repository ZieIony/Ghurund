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

        ~SystemCollection() {
            clear();
        }

        inline void add(IntrusivePointer<System> system) {
            system->init();
            systems.add(system);
            gameObjects.add(system);
        }

        inline void remove(IntrusivePointer<System> system) {
            gameObjects.remove(system);
            systems.remove(system);
            system->uninit();
        }

        inline void clear() {
            while (!systems.Empty) {
                auto system = systems.get(systems.Size - 1);
                systems.removeAt(systems.Size - 1);
                gameObjects.remove(system);
                system->uninit();
            }
        }
    };
}
