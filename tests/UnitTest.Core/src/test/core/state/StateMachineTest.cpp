#include "utcpch.h"
#include "CppUnitTest.h"

#include "core/state/StateMachine.h"
#include "test/utils/MemoryGuard.h"
#include "test/utils/ObjectGuard.h"
#include "test/utils/TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	using namespace UnitTest::Utils;
	using namespace Ghurund::Core;
	using namespace std;

	class TestStateIdle:public MachineState {
	public:
		TestStateIdle():MachineState(_T("idle"), true) {}
	};

	class TestStateInProgress:public MachineState {
	public:
		TestStateInProgress():MachineState(_T("inProgress"), false) {}
	};

	class TestStateSuccess:public MachineState {
	public:
		TestStateSuccess():MachineState(_T("success"), false) {}
	};

	class TestStateError:public MachineState {
	public:
		TestStateError():MachineState(_T("error"), true) {}
	};

	TEST_CLASS(StateMachineTest) {
	public:

		TEST_METHOD(StateMachine_goTo) {
			MemoryGuard mg;
			ObjectGuard og;
			{
				StateMachine machine;
				auto idle = makeIntrusive<TestStateIdle>();
				auto inProgress = makeIntrusive<TestStateInProgress>();
				auto transition = makeIntrusive<StateTransition>(idle.ref(), inProgress.ref());
				machine.putState(idle.get());
				machine.putState(inProgress.get());
				machine.putTransition(transition.get());

				machine.reset(idle.ref());
				Assert::IsTrue(machine.CurrentState == idle.get());

				machine.goTo(inProgress.ref());
				Assert::IsTrue(machine.CurrentState == inProgress.get());
			}
		}

		TEST_METHOD(StateMachine_goTo_sameState) {
			MemoryGuard mg;
			ObjectGuard og;
			{
				StateMachine machine;
				auto idle = makeIntrusive<TestStateIdle>();
				auto inProgress = makeIntrusive<TestStateInProgress>();
				auto transition = makeIntrusive<StateTransition>(idle.ref(), inProgress.ref());
				machine.putState(idle.get());
				machine.putState(inProgress.get());
				machine.putTransition(transition.get());

				machine.reset(idle.ref());
				Assert::IsTrue(machine.CurrentState == idle.get());

				machine.goTo(idle.ref());
				Assert::IsTrue(machine.CurrentState == idle.get());
			}
		}

		TEST_METHOD(StateMachine_goTo_noTransition) {
			MemoryGuard mg;
			ObjectGuard og;
			{
				StateMachine machine;
				auto idle = makeIntrusive<TestStateIdle>();
				auto inProgress = makeIntrusive<TestStateInProgress>();
				machine.putState(idle.get());
				machine.putState(inProgress.get());

				machine.reset(idle.ref());
				Assert::IsTrue(machine.CurrentState == idle.get());

				Assert::ExpectException<std::invalid_argument>([&] {
					machine.goTo(inProgress.ref());
				});
				Assert::IsTrue(machine.CurrentState == idle.get());
			}
		}

		TEST_METHOD(StateMachine_goTo_noState) {
			MemoryGuard mg;
			ObjectGuard og;
			{
				StateMachine machine;
				auto idle = makeIntrusive<TestStateIdle>();
				machine.putState(idle.get());

				machine.reset(idle.ref());
				Assert::IsTrue(machine.CurrentState == idle.get());

				Assert::ExpectException<std::invalid_argument>([&] {
					machine.goTo(_T("inProgress"));
				});
				Assert::IsTrue(machine.CurrentState == idle.get());
			}
		}

		TEST_METHOD(StateMachine_jumpTo) {
			MemoryGuard mg;
			ObjectGuard og;
			{
				StateMachine machine;
				auto idle = makeIntrusive<TestStateIdle>();
				auto error = makeIntrusive<TestStateError>();
				machine.putState(idle.get());
				machine.putState(error.get());

				machine.reset(idle.ref());
				Assert::IsTrue(machine.CurrentState == idle.get());

				machine.jumpTo(error.ref());
				Assert::IsTrue(machine.CurrentState == error.get());
			}
		}

		TEST_METHOD(StateMachine_jumpTo_sameState) {
			MemoryGuard mg;
			ObjectGuard og;
			{
				StateMachine machine;
				auto idle = makeIntrusive<TestStateIdle>();
				auto error = makeIntrusive<TestStateError>();
				machine.putState(idle.get());
				machine.putState(error.get());

				machine.reset(idle.ref());
				Assert::IsTrue(machine.CurrentState == idle.get());

				machine.jumpTo(idle.ref());
				Assert::IsTrue(machine.CurrentState == idle.get());
			}
		}

		TEST_METHOD(StateMachine_jumpTo_notJumpable) {
			MemoryGuard mg;
			ObjectGuard og;
			{
				StateMachine machine;
				auto idle = makeIntrusive<TestStateIdle>();
				auto success = makeIntrusive<TestStateSuccess>();
				machine.putState(idle.get());
				machine.putState(success.get());

				machine.reset(idle.ref());
				Assert::IsTrue(machine.CurrentState == idle.get());

				Assert::ExpectException<std::invalid_argument>([&] {
					machine.jumpTo(success.ref());
				});
				Assert::IsTrue(machine.CurrentState == idle.get());
			}
		}

		TEST_METHOD(StateMachine_jumpTo_noState) {
			MemoryGuard mg;
			ObjectGuard og;
			{
				StateMachine machine;
				auto idle = makeIntrusive<TestStateIdle>();
				machine.putState(idle.get());

				machine.reset(idle.ref());
				Assert::IsTrue(machine.CurrentState == idle.get());

				Assert::ExpectException<std::invalid_argument>([&] {
					machine.jumpTo(_T("success"));
				});
				Assert::IsTrue(machine.CurrentState == idle.get());
			}
		}

		TEST_METHOD(StateMachine_update) {
			MemoryGuard mg;
			ObjectGuard og;
			{
				StateMachine machine;
				auto idle = makeIntrusive<TestStateIdle>();
				auto inProgress = makeIntrusive<TestStateInProgress>();
				auto transition = makeIntrusive<StateTransition>(idle.ref(), inProgress.ref());
				machine.putState(idle.get());
				machine.putState(inProgress.get());
				machine.putTransition(transition.get());

				machine.reset(idle.ref());
				Assert::IsTrue(machine.CurrentState == idle.get());

				machine.update();
				Assert::IsTrue(machine.CurrentState == inProgress.get());

				machine.update();
				Assert::IsTrue(machine.CurrentState == inProgress.get());
			}
		}
	};
}
