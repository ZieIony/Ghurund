#include "ute2dpch.h"
#include "CppUnitTest.h"

#include "core/object/IntrusivePointer.h"
#include "core/reflection/StandardTypes.h"
#include "test/utils/MemoryGuard.h"
#include "engine/2d/World2D.h"

#include <test/2d/Test2DContext.h>
#include "ComponentTestUtils.h"
#include <test/utils/ObjectGuard.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::_2D;
    using namespace std;

    TEST_CLASS(TransformComponent2DTest) {
private:
    GameApplication app;
    Test2DContext context2d;
    SharedPointer<World2D> world;

public:
    TransformComponent2DTest() {
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

    TEST_METHOD(TransformComponent2D_doubleInit) {
        //MemoryGuard guard; // box2d allocates on init
        ObjectGuard guard;
        {
            auto component = makeComponent<TransformComponent2D>(world.ref());

            auto coroutine = component->init();
            coroutine.resume();
            auto coroutine2 = component->init();
            coroutine2.resume();

            destroyComponent(world.ref(), component);
        }
    }


    TEST_METHOD(TransformComponent2D_position) {
        //MemoryGuard guard; // box2d allocates on init
        ObjectGuard guard;
        {
            auto component = makeComponent<TransformComponent2D>(world.ref());
            auto coroutine = component->init();
            coroutine.resume();

            component->Position = { 100, 30 };
            Assert::AreEqual(100.0f, component->Position.x);
            Assert::AreEqual(30.0f, component->Position.y);

            destroyComponent(world.ref(), component);
        }
    }

    TEST_METHOD(TransformComponent2D_position_uninitialized) {
        //MemoryGuard guard; // box2d allocates on init
        ObjectGuard guard;
        {
            auto component = makeComponent<TransformComponent2D>(world.ref());

            component->Position = { 100, 30 };
            Assert::AreEqual(100.0f, component->Position.x);
            Assert::AreEqual(30.0f, component->Position.y);

            destroyComponent(world.ref(), component);
        }
    }

    TEST_METHOD(TransformComponent2D_scale) {
        //MemoryGuard guard; // box2d allocates on init
        ObjectGuard guard;
        {
            auto component = makeComponent<TransformComponent2D>(world.ref());
            auto coroutine = component->init();
            coroutine.resume();

            component->Scale = { 2, 3 };
            Assert::AreEqual(2.0f, component->Scale.x);
            Assert::AreEqual(3.0f, component->Scale.y);

            destroyComponent(world.ref(), component);
        }
    }

    TEST_METHOD(TransformComponent2D_scale_uninitialized) {
        //MemoryGuard guard; // box2d allocates on init
        ObjectGuard guard;
        {
            auto component = makeComponent<TransformComponent2D>(world.ref());

            component->Scale = { 2, 3 };
            Assert::AreEqual(2.0f, component->Scale.x);
            Assert::AreEqual(3.0f, component->Scale.y);
   
            destroyComponent(world.ref(), component);
        }
    }

    TEST_METHOD(TransformComponent2D_rotation) {
        //MemoryGuard guard; // box2d allocates on init
        ObjectGuard guard;
        {
            auto component = makeComponent<TransformComponent2D>(world.ref());
            auto coroutine = component->init();
            coroutine.resume();

            component->Rotation = 90.0f;
            Assert::AreEqual(90.0f, component->Rotation);
    
            destroyComponent(world.ref(), component);
        }
    }

    TEST_METHOD(TransformComponent2D_rotation_uninitialized) {
        //MemoryGuard guard; // box2d allocates on init
        ObjectGuard guard;
        {
            auto component = makeComponent<TransformComponent2D>(world.ref());

            component->Rotation = 90.0f;
            Assert::AreEqual(90.0f, component->Rotation);
  
            destroyComponent(world.ref(), component);
        }
    }
    };
}
