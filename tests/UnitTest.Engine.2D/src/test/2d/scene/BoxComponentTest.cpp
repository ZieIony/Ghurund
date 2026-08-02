#include "ute2dpch.h"
#include "CppUnitTest.h"

#include "core/object/IntrusivePointer.h"
#include "core/reflection/StandardTypes.h"
#include "engine/2d/physics/component/BoxComponent2D.h"
#include "engine/2d/World2D.h"

#include "core/logging/Logger.h"
#include <test/2d/Test2DContext.h>
#include "ComponentTestUtils.h"
#include "test/utils/ObjectGuard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::_2D;
    using namespace std;

    class TestBoxComponent2D:public BoxComponent2D {
    public:
        TestBoxComponent2D(NotNull<Entity2D> owner):BoxComponent2D(owner) {
            isVisualized = false;
        }
    };

    TEST_CLASS(BoxComponentTest) {
private:
    GameApplication app;
    Test2DContext context2d;
    SharedPointer<World2D> world;

public:
    BoxComponentTest() {
        world = makeShared<World2D>(app, context2d);
    }

    TEST_CLASS_INITIALIZE(construct) {
        Ghurund::Core::Logger::init();
    }

    TEST_METHOD_INITIALIZE(init) {
        world->init();
    }

    TEST_METHOD_CLEANUP(uninit) {
        world->uninit();
    }

    TEST_METHOD(BoxComponent_doubleInit) {
        //MemoryGuard guard; // box2d allocates on init
        ObjectGuard guard;
        {
            auto component = makeComponent<TestBoxComponent2D>(world.ref());

            auto coroutine = component->init();
            coroutine.resume();
            auto coroutine2 = component->init();
            coroutine2.resume();

            destroyComponent(world.ref(), component);
        }
    }


    TEST_METHOD(BoxComponent_position) {
        //MemoryGuard guard; // box2d allocates on init
        ObjectGuard guard;
        {
            auto component = makeComponent<TestBoxComponent2D>(world.ref());

            auto coroutine = component->init();
            coroutine.resume();
            component->Position = { 100, 30 };
            Assert::AreEqual(100.0f, component->Position.x);
            Assert::AreEqual(30.0f, component->Position.y);

            destroyComponent(world.ref(), component);
        }
    }

    TEST_METHOD(BoxComponent_size) {
        //MemoryGuard guard; // box2d allocates on init
        ObjectGuard guard;
        {
            auto component = makeComponent<TestBoxComponent2D>(world.ref());

            auto coroutine = component->init();
            coroutine.resume();
            component->Size = { 100, 30 };
            Assert::AreEqual(100.0f, component->Size.Width);
            Assert::AreEqual(30.0f, component->Size.Height);

            destroyComponent(world.ref(), component);
        }
    }

    TEST_METHOD(BoxComponent_rotation) {
        //MemoryGuard guard; // box2d allocates on init
        ObjectGuard guard;
        {
            auto component = makeComponent<TestBoxComponent2D>(world.ref());

            auto coroutine = component->init();
            coroutine.resume();
            component->Rotation = 90.0f;
            Assert::AreEqual(90.0f, component->Rotation);

            destroyComponent(world.ref(), component);
        }
    }
    };
}
