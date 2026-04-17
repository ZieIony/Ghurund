#include "utepch.h"
#include "CppUnitTest.h"

#include "core/object/IntrusivePointer.h"
#include "core/reflection/StandardTypes.h"
#include "engine/2d/physics/component/BoxComponent2D.h"
#include "test/utils/MemoryGuard.h"
#include "engine/2d/physics/Simulation2D.h"
#include "engine/2d/World2D.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::_2D;
    using namespace std;

    TEST_CLASS(BoxComponentTest) {
private:
    World2D world;
    Simulation2D simulation;

    template<typename T>
    T* makeComponent() {
        auto coroutine = world.spawnEntity<Entity2D>();
        coroutine.resume();
        auto owner = coroutine.Result;
        return owner->makeComponent<BoxComponent2D>();
    }

public:
    BoxComponentTest() {
        world.simulation = &simulation;
    }

    TEST_METHOD(BoxComponent_doubleInit) {
        MemoryGuard guard;
        {
            auto component = makeComponent<BoxComponent2D>();

            component->init();
            component->init();
        }
    }


    TEST_METHOD(BoxComponent_position) {
        MemoryGuard guard;
        {
            auto component = makeComponent<BoxComponent2D>();

            component->init();
            component->Position = { 100, 30 };
            Assert::AreEqual(100.0f, component->Position.x);
            Assert::AreEqual(30.0f, component->Position.y);
        }
    }

    TEST_METHOD(BoxComponent_size) {
        MemoryGuard guard;
        {
            auto component = makeComponent<BoxComponent2D>();

            component->init();
            component->Size = { 100, 30 };
            Assert::AreEqual(100.0f, component->Size.Width);
            Assert::AreEqual(30.0f, component->Size.Height);
        }
    }

    TEST_METHOD(BoxComponent_rotation) {
        MemoryGuard guard;
        {
            auto component = makeComponent<BoxComponent2D>();

            component->init();
            component->Rotation = 90.0f;
            Assert::AreEqual(90.0f, component->Rotation);
        }
    }
    };
}
