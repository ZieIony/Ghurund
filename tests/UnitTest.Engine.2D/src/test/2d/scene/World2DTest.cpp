#include "ute2dpch.h"
#include "CppUnitTest.h"

#include "core/reflection/StandardTypes.h"
#include "test/utils/MemoryGuard.h"
#include "engine/2d/World2D.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::_2D;
    using namespace std;

    TEST_CLASS(World2DTest) {
private:
    GameApplication app;
    SharedPointer<World2D> world;

public:
    World2DTest() {
        world = makeShared<World2D>(app);
    }

    TEST_METHOD_INITIALIZE(init) {
        world->init();
    }

    TEST_METHOD_CLEANUP(uninit) {
        world->deinit();
    }

    TEST_METHOD(World2D_spawnDestroyEntity) {
        // MemoryGuard guard;   // entt allocates stuff to spawn entities
        {
            auto entity = world->spawnEntity<Entity>();
            world->destroyEntity(entity);
        }
    }
    };
}
