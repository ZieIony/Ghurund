#include "ute2dpch.h"
#include "CppUnitTest.h"

#include "core/object/IntrusivePointer.h"
#include "core/reflection/StandardTypes.h"
#include "engine/2d/physics/RigidBodyComponent2D.h"
#include "engine/2d/World2D.h"

#include "core/logging/Logger.h"
#include "test/utils/ObjectGuard.h"
#include "test/utils/TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::_2D;
    using namespace std;

    TEST_CLASS(CapsuleComponentTest) {
    private:
        GameApplication app;
        SharedPointer<World2D> world;
        IntrusivePointer<PhysicsSystem2D> physicsSystem;

    public:
        CapsuleComponentTest() {
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

        TEST_METHOD(CapsuleComponent_doubleInit) {
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


        TEST_METHOD(CapsuleComponent_position) {
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

        TEST_METHOD(CapsuleComponent_size) {
            //MemoryGuard guard; // box2d allocates on init
            ObjectGuard guard;
            {
                auto entity = world->spawnEntity<Entity>();
                auto component = entity.addComponent<RigidBodyComponent2D>();
                component.init(physicsSystem.ref(), ShapeType::CAPSULE);

                component.setSize(30, 100);
                Assert::AreEqual(30.0f, component.Size.Width);
                Assert::AreEqual(100.0f, component.Size.Height);

                entity.removeComponent<RigidBodyComponent2D>();
                world->destroyEntity(entity);
            }
        }

        TEST_METHOD(CapsuleComponent_rotation) {
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
