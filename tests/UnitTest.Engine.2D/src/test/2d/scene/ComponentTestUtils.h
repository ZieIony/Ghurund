#pragma once

#include "core/concepts/Concepts.h"
#include "core/object/IntrusivePointer.h"
#include "engine/2d/scene/component/Component2D.h"
#include "engine/2d/World2D.h"

namespace UnitTest::Utils {
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine::_2D;

    template<Derived<Component2D> T>
    T* makeComponent(World2D& world) {
        auto coroutine = world.spawnEntity<Entity2D>();
        coroutine.resume();
        auto owner = coroutine.Result;  // owner gets released because the coroutine is already destroyed, but it's fine, because owner has more references elsewhere
        auto component = owner->makeComponent<T>();
        owner->Components.add(component);
        return component;
    }

    template<Derived<Component2D> T>
    void destroyComponent(World2D& world, T* component) {
        auto owner = IntrusivePointer<Entity2D>(&component->Owner);
        component->release();
        owner->addReference();
        world.destroyEntity(owner);
    }
}
