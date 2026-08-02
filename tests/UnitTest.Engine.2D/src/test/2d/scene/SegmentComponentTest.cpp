#include "ute2dpch.h"
#include "CppUnitTest.h"

#include "core/object/IntrusivePointer.h"
#include "core/reflection/StandardTypes.h"
#include "engine/2d/physics/component/SegmentComponent2D.h"
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

    class TestSegmentComponent2D:public SegmentComponent2D {
    public:
        TestSegmentComponent2D(NotNull<Entity2D> owner):SegmentComponent2D(owner) {
            isVisualized = false;
        }
    };

    TEST_CLASS(SegmentComponentTest) {
    private:
        GameApplication app;
        Test2DContext context2d;
        SharedPointer<World2D> world;

    public:
        SegmentComponentTest() {
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

        TEST_METHOD(SegmentComponent_doubleInit) {
            //MemoryGuard guard; // box2d allocates on init
            ObjectGuard guard;
            {
                auto component = makeComponent<TestSegmentComponent2D>(world.ref());

                auto coroutine = component->init();
                coroutine.resume();
                auto coroutine2 = component->init();
                coroutine2.resume();

                destroyComponent(world.ref(), component);
            }
        }


        TEST_METHOD(SegmentComponent_position) {
            //MemoryGuard guard; // box2d allocates on init
            ObjectGuard guard;
            {
                auto component = makeComponent<TestSegmentComponent2D>(world.ref());

                auto coroutine = component->init();
                coroutine.resume();
                component->Position = { 100, 30 };
                Assert::AreEqual(100.0f, component->Position.x);
                Assert::AreEqual(30.0f, component->Position.y);

                destroyComponent(world.ref(), component);
            }
        }

        TEST_METHOD(SegmentComponent_width) {
            //MemoryGuard guard; // box2d allocates on init
            ObjectGuard guard;
            {
                auto component = makeComponent<TestSegmentComponent2D>(world.ref());

                auto coroutine = component->init();
                coroutine.resume();
                component->Width = 100;
                Assert::AreEqual(100.0f, component->Width);

                destroyComponent(world.ref(), component);
            }
        }

        TEST_METHOD(SegmentComponent_rotation) {
            //MemoryGuard guard; // box2d allocates on init
            ObjectGuard guard;
            {
                auto component = makeComponent<TestSegmentComponent2D>(world.ref());

                auto coroutine = component->init();
                coroutine.resume();
                component->Rotation = 90.0f;
                Assert::AreEqual(90.0f, component->Rotation);

                destroyComponent(world.ref(), component);
            }
        }
    };
}
