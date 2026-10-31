#include "ute2dpch.h"
#include "CppUnitTest.h"

#include "core/object/IntrusivePointer.h"
#include "core/reflection/StandardTypes.h"
#include <engine/2d/physics/RigidBodyComponent2D.h>
#include "engine/2d/World2D.h"

#include "core/logging/Logger.h"
#include "test/utils/ObjectGuard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::_2D;
    using namespace std;

    TEST_CLASS(SegmentComponentTest) {
    private:
        GameApplication app;
        SharedPointer<World2D> world;
        IntrusivePointer<PhysicsSystem2D> physicsSystem;

    public:
        SegmentComponentTest() {
            world = makeShared<World2D>(app);
            physicsSystem = makeIntrusive<PhysicsSystem2D>(world.ref());
        }

        TEST_CLASS_INITIALIZE(construct) {
            Ghurund::Core::Logger::init();
        }

        TEST_METHOD_INITIALIZE(init) {
            world->init();
            physicsSystem->init();
        }

        TEST_METHOD_CLEANUP(uninit) {
            physicsSystem->deinit();
            world->deinit();
        }

        TEST_METHOD(SegmentComponent_doubleInit) {
            //MemoryGuard guard; // box2d allocates on init
            ObjectGuard guard;
            {
                auto entity = world->spawnEntity<Entity>();
                auto component = entity.addComponent<RigidBodyComponent2D>();

                component.init(physicsSystem.ref(), ShapeType::CAPSULE);
                component.init(physicsSystem.ref(), ShapeType::CAPSULE);

                entity.removeComponent<RigidBodyComponent2D>();
                world->destroyEntity(entity);
            }
        }


        TEST_METHOD(SegmentComponent_position) {
            //MemoryGuard guard; // box2d allocates on init
            ObjectGuard guard;
            {
                auto entity = world->spawnEntity<Entity>();
                auto component = entity.addComponent<RigidBodyComponent2D>();
                component.init(physicsSystem.ref(), ShapeType::CAPSULE);

                component.Position = { 100, 30 };
                Assert::AreEqual(100.0f, component.Position.x);
                Assert::AreEqual(30.0f, component.Position.y);

                entity.removeComponent<RigidBodyComponent2D>();
                world->destroyEntity(entity);
            }
        }

        TEST_METHOD(SegmentComponent_width) {
            //MemoryGuard guard; // box2d allocates on init
            ObjectGuard guard;
            {
                auto entity = world->spawnEntity<Entity>();
                auto component = entity.addComponent<RigidBodyComponent2D>();
                component.init(physicsSystem.ref(), ShapeType::CAPSULE);

                component.setSize(100, 1);
                Assert::AreEqual(100.0f, component.Size.Width);

                entity.removeComponent<RigidBodyComponent2D>();
                world->destroyEntity(entity);
            }
        }

        TEST_METHOD(SegmentComponent_rotation) {
            //MemoryGuard guard; // box2d allocates on init
            ObjectGuard guard;
            {
                auto entity = world->spawnEntity<Entity>();
                auto component = entity.addComponent<RigidBodyComponent2D>();
                component.init(physicsSystem.ref(), ShapeType::CAPSULE);

                component.Rotation = 90.0f;
                Assert::AreEqual(90.0f, component.Rotation);

                entity.removeComponent<RigidBodyComponent2D>();
                world->destroyEntity(entity);
            }
        }
    };
}
