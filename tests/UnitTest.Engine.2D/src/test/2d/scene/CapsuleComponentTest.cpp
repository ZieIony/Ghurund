#include "ute2dpch.h"
#include "CppUnitTest.h"

#include "core/object/IntrusivePointer.h"
#include "core/reflection/StandardTypes.h"
#include "engine/2d/physics/component/CapsuleComponent2D.h"
#include "engine/2d/World2D.h"

#include "core/logging/Logger.h"
#include "ComponentTestUtils.h"
#include "test/utils/ObjectGuard.h"
#include "test/utils/TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::_2D;
    using namespace std;

    class TestCapsuleComponent2D:public CapsuleComponent2D {
    public:
        TestCapsuleComponent2D(NotNull<Entity2D> owner):CapsuleComponent2D(owner) {
            isVisualized = false;
        }
    };

    TEST_CLASS(CapsuleComponentTest) {
    private:
        GameApplication app;
        SharedPointer<World2D> world;

    public:
        CapsuleComponentTest() {
            world = makeShared<World2D>(app);
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

        TEST_METHOD(CapsuleComponent_doubleInit) {
            //MemoryGuard guard; // box2d allocates on init
            ObjectGuard guard;
            {
                auto component = makeComponent<TestCapsuleComponent2D>(world.ref());

                runCoroutineBlocking(component->init());
                runCoroutineBlocking(component->init());

                destroyComponent(world.ref(), component);
            }
        }


        TEST_METHOD(CapsuleComponent_position) {
            //MemoryGuard guard; // box2d allocates on init
            ObjectGuard guard;
            {
                auto component = makeComponent<TestCapsuleComponent2D>(world.ref());

                auto coroutine = component->init();
                coroutine.resume();
                component->Position = { 100, 30 };
                Assert::AreEqual(100.0f, component->Position.x);
                Assert::AreEqual(30.0f, component->Position.y);

                destroyComponent(world.ref(), component);
            }
        }

        TEST_METHOD(CapsuleComponent_heightRadius) {
            //MemoryGuard guard; // box2d allocates on init
            ObjectGuard guard;
            {
                auto component = makeComponent<TestCapsuleComponent2D>(world.ref());

                auto coroutine = component->init();
                coroutine.resume();
                component->setHeightRadius(100, 30);
                Assert::AreEqual(100.0f, component->Height);
                Assert::AreEqual(30.0f, component->Radius);

                destroyComponent(world.ref(), component);
            }
        }

        TEST_METHOD(CapsuleComponent_rotation) {
            //MemoryGuard guard; // box2d allocates on init
            ObjectGuard guard;
            {
                auto component = makeComponent<TestCapsuleComponent2D>(world.ref());

                auto coroutine = component->init();
                coroutine.resume();
                component->Rotation = 90.0f;
                Assert::AreEqual(90.0f, component->Rotation);

                destroyComponent(world.ref(), component);
            }
        }
    };
}
