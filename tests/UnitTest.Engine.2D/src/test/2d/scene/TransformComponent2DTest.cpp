#include "ute2dpch.h"
#include "CppUnitTest.h"

#include "core/object/IntrusivePointer.h"
#include "core/reflection/StandardTypes.h"
#include "test/utils/MemoryGuard.h"
#include "engine/2d/World2D.h"
#include <engine/2d/scene/transform/TransformComponent2D.h>
#include "core/math/Matrix.h"

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
    SharedPointer<World2D> world;
    IntrusivePointer<PhysicsSystem2D> physicsSystem;

public:
    TransformComponent2DTest() {
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

    TEST_METHOD(TransformComponent2D_position) {
        //MemoryGuard guard; // box2d allocates on init
        ObjectGuard guard;
        {
            auto entity = world->spawnEntity<Entity>();
            auto component = entity.addComponent<TransformComponent2D>();

            component.Position = { 100, 30 };
            Assert::AreEqual(100.0f, component.Position.x);
            Assert::AreEqual(30.0f, component.Position.y);

            entity.removeComponent<TransformComponent2D>();
            world->destroyEntity(entity);
        }
    }

    TEST_METHOD(TransformComponent2D_scale) {
        //MemoryGuard guard; // box2d allocates on init
        ObjectGuard guard;
        {
            auto entity = world->spawnEntity<Entity>();
            auto component = entity.addComponent<TransformComponent2D>();

            component.Scale = { 2, 3 };
            Assert::AreEqual(2.0f, component.Scale.x);
            Assert::AreEqual(3.0f, component.Scale.y);

            entity.removeComponent<TransformComponent2D>();
            world->destroyEntity(entity);
        }
    }

    TEST_METHOD(TransformComponent2D_rotation) {
        //MemoryGuard guard; // box2d allocates on init
        ObjectGuard guard;
        {
            auto entity = world->spawnEntity<Entity>();
            auto component = entity.addComponent<TransformComponent2D>();

            component.Rotation = 90.0f;
            Assert::AreEqual(90.0f, component.Rotation);
    
            entity.removeComponent<TransformComponent2D>();
            world->destroyEntity(entity);
        }
    }

    TEST_METHOD(TransformComponent2D_update) {
        //MemoryGuard guard; // box2d allocates on init
        ObjectGuard guard;
        {
            auto entity = world->spawnEntity<Entity>();
            auto component = entity.addComponent<TransformComponent2D>();

            component.Position = { 2, 3 };
            component.Rotation = 5;
            component.Scale = { 3, 4 };
            component.update();

            auto identity = makeIdentityMatrix();
			Assert::IsFalse(memcmp(&component.WorldTransformation, &identity, sizeof(XMFLOAT4X4)) == 0);
  
            entity.removeComponent<TransformComponent2D>();
            world->destroyEntity(entity);
        }
    }
    };
}
