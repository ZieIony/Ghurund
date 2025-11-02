#include "utepch.h"
#include "CppUnitTest.h"

#include "engine/game/action/ActionMapping.h"
#include <core/object/IntrusivePointer.h>

#include "TestGameAction.h"
#include "test/utils/MemoryGuard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::Engine;
    using namespace UnitTest::Utils;

    TEST_CLASS(FloatGameActionTest) {
public:

    TEST_METHOD(FloatGameAction_threshold) {
        MemoryGuard guard;
        {
            auto action = makeIntrusive<TestFloatAction>(0.1f);
            InputDispatcher<float> dispatcher(action.get(), 0);

            dispatcher.makeDispatchEventTask(0.2f, 0)->execute();
            Assert::IsTrue(TestActionState::STARTED == action->state);
            dispatcher.makeDispatchEventTask(0.5f, 0)->execute();
            Assert::IsTrue(TestActionState::IN_PROGRESS == action->state);
            dispatcher.makeDispatchEventTask(0.0f, 0)->execute();
            Assert::IsTrue(TestActionState::FINISHED == action->state);
        }
    }

    TEST_METHOD(FloatGameAction_belowThreshold) {
        MemoryGuard guard;
        {
            auto action = makeIntrusive<TestFloatAction>(0.1f);
            InputDispatcher<float> dispatcher(action.get(), 0);

            dispatcher.makeDispatchEventTask(0.0f, 0)->execute();
            Assert::IsTrue(TestActionState::IDLE == action->state);
            dispatcher.makeDispatchEventTask(0.01f, 0)->execute();
            Assert::IsTrue(TestActionState::IDLE == action->state);
            dispatcher.makeDispatchEventTask(0.02f, 0)->execute();
            Assert::IsTrue(TestActionState::IDLE == action->state);
        }
    }
    };
}
