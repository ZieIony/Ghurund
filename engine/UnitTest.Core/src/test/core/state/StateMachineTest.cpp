#include "pch.h"
#include "CppUnitTest.h"

#include "core/state/StateMachine.h"
#include "test/MemoryGuard.h"
#include "test/TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	using namespace UnitTest::Utils;
	using namespace Ghurund::Core;
	using namespace std;

	enum class TestEnum {
		IDLE, IN_PROGRESS, SUCCESS, ERR0R
	};

	TEST_CLASS(StateMachineTest) {
	public:

		TEST_METHOD(StateMachine_required) {
			MemoryGuard guard;
			{
				StateMachine<TestEnum> machine(TestEnum::IDLE, StateMachineEdgeMode::REQUIRED);
				machine.addState(TestEnum::IN_PROGRESS);
				machine.addEdge(TestEnum::IDLE, TestEnum::IN_PROGRESS);
				machine.State = TestEnum::IN_PROGRESS;
			}
		}

		TEST_METHOD(StateMachine_requiredNoEdge) {
			MemoryGuard guard;
			{
				StateMachine<TestEnum> machine(TestEnum::IDLE, StateMachineEdgeMode::REQUIRED);
				machine.addState(TestEnum::IN_PROGRESS);
				Assert::ExpectException<InvalidParamException>([&] {
					machine.State = TestEnum::IN_PROGRESS;
				});
			}
		}

		TEST_METHOD(StateMachine_requiredSameState) {
			MemoryGuard guard;
			{
				StateMachine<TestEnum> machine(TestEnum::IDLE, StateMachineEdgeMode::REQUIRED);
				machine.addState(TestEnum::IDLE);
				Assert::ExpectException<InvalidParamException>([&] {
					machine.State = TestEnum::IDLE;
				});
			}
		}

		TEST_METHOD(StateMachine_requiredNoState) {
			MemoryGuard guard;
			{
				StateMachine<TestEnum> machine(TestEnum::IDLE, StateMachineEdgeMode::REQUIRED);
				Assert::ExpectException<InvalidParamException>([&] {
					machine.State = TestEnum::IN_PROGRESS;
				});
			}
		}

		TEST_METHOD(StateMachine_same) {
			MemoryGuard guard;
			{
				StateMachine<TestEnum> machine(TestEnum::IDLE, StateMachineEdgeMode::SAME_STATE_ALLOWED);
				machine.addState(TestEnum::IN_PROGRESS);
				machine.addEdge(TestEnum::IDLE, TestEnum::IN_PROGRESS);
				machine.State = TestEnum::IN_PROGRESS;
			}
		}

		TEST_METHOD(StateMachine_sameNoEdge) {
			MemoryGuard guard;
			{
				StateMachine<TestEnum> machine(TestEnum::IDLE, StateMachineEdgeMode::SAME_STATE_ALLOWED);
				machine.addState(TestEnum::IN_PROGRESS);
				Assert::ExpectException<InvalidParamException>([&] {
					machine.State = TestEnum::IN_PROGRESS;
				});
			}
		}

		TEST_METHOD(StateMachine_sameSameState) {
			MemoryGuard guard;
			{
				StateMachine<TestEnum> machine(TestEnum::IDLE, StateMachineEdgeMode::SAME_STATE_ALLOWED);
				machine.addState(TestEnum::IDLE);
				machine.State = TestEnum::IDLE;
			}
		}

		TEST_METHOD(StateMachine_sameNoState) {
			MemoryGuard guard;
			{
				StateMachine<TestEnum> machine(TestEnum::IDLE, StateMachineEdgeMode::SAME_STATE_ALLOWED);
				Assert::ExpectException<InvalidParamException>([&] {
					machine.State = TestEnum::IN_PROGRESS;
				});
			}
		}

		TEST_METHOD(StateMachine_any) {
			MemoryGuard guard;
			{
				StateMachine<TestEnum> machine(TestEnum::IDLE, StateMachineEdgeMode::ANY_STATE_ALLOWED);
				machine.addState(TestEnum::IN_PROGRESS);
				machine.addEdge(TestEnum::IDLE, TestEnum::IN_PROGRESS);
				machine.State = TestEnum::IN_PROGRESS;
			}
		}

		TEST_METHOD(StateMachine_anyNoEdge) {
			MemoryGuard guard;
			{
				StateMachine<TestEnum> machine(TestEnum::IDLE, StateMachineEdgeMode::ANY_STATE_ALLOWED);
				machine.addState(TestEnum::IN_PROGRESS);
				machine.State = TestEnum::IN_PROGRESS;
			}
		}

		TEST_METHOD(StateMachine_anySameState) {
			MemoryGuard guard;
			{
				StateMachine<TestEnum> machine(TestEnum::IDLE, StateMachineEdgeMode::ANY_STATE_ALLOWED);
				machine.addState(TestEnum::IDLE);
				machine.State = TestEnum::IDLE;
			}
		}

		TEST_METHOD(StateMachine_anyNoState) {
			MemoryGuard guard;
			{
				StateMachine<TestEnum> machine(TestEnum::IDLE, StateMachineEdgeMode::ANY_STATE_ALLOWED);
				Assert::ExpectException<InvalidParamException>([&] {
					machine.State = TestEnum::IN_PROGRESS;
				});
			}
		}
	};
}
