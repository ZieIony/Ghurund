#include "utepch.h"
#include "CppUnitTest.h"

#include "core/object/IntrusivePointer.h"
#include "core/reflection/StandardTypes.h"
#include "engine/2d/physics/BoxComponent2D.h"
#include "test/utils/MemoryGuard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::_2D;
    using namespace std;

    TEST_CLASS(BoxComponentTest) {
private:

public:
    TEST_METHOD(BoxComponent_position) {
        MemoryGuard guard;
        {
            World2D world;
            BoxComponent2D component;
            component.init(world);
            component.Position = { 100, 30 };
            Assert::AreEqual(100.0f, component.Position.x);
            Assert::AreEqual(30.0f, component.Position.y);
        }
    }

    TEST_METHOD(BoxComponent_size) {
        MemoryGuard guard;
        {
            World2D world;
            BoxComponent2D component;
            component.init(world);
            component.Size = { 100, 30 };
            Assert::AreEqual(100.0f, component.Size.Width);
            Assert::AreEqual(30.0f, component.Size.Height);
        }
    }

    TEST_METHOD(BoxComponent_rotation) {
        MemoryGuard guard;
        {
            World2D world;
            BoxComponent2D component;
            component.init(world);
            component.Rotation = 90.0f;
            Assert::AreEqual(90.0f, component.Rotation);
        }
    }
    };
}
