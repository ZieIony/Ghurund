#include "ute2dpch.h"
#include "CppUnitTest.h"

#include "core/object/IntrusivePointer.h"
#include "core/reflection/StandardTypes.h"
#include "test/utils/MemoryGuard.h"
#include "engine/2d/World2D.h"
#include <test/2d/Test2DContext.h>

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
    Test2DContext context2d;
    SharedPointer<World2D> world;

public:
    World2DTest() {
        world = makeShared<World2D>(app, context2d);
    }

    TEST_METHOD_INITIALIZE(init) {
        world->init();
    }

    TEST_METHOD_CLEANUP(uninit) {
        world->uninit();
    }

    TEST_METHOD(World2D_spawnDestroyEntity) {
        MemoryGuard guard;
        {
            auto coroutine = world->spawnEntity<Entity2D>();
            coroutine.resume();
            auto entity = coroutine.Result;
            world->destroyEntity(entity);
        }
    }
    };
}
