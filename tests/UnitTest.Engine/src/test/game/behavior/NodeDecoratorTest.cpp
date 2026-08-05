#include "utepch.h"
#include "CppUnitTest.h"

#include "TestNodes.h"
#include "TestDecorators.h"
#include "test/utils/MemoryGuard.h"
#include <core/object/IntrusivePointer.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	using namespace Ghurund::Engine;
	using namespace UnitTest::Utils;

	TEST_CLASS(NodeDecoratorTest) {
public:

	TEST_METHOD(NodeDecorator_successExecuted) {
		MemoryGuard guard;
		{
			auto blackboard = makeIntrusive<Blackboard>();
			auto decorator = makeIntrusive<TestExecuteDecorator>();
			auto node = makeIntrusive<TestSuccessNode>();
			node->decorators.add(decorator.get());

			auto result = node->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::SUCCESS == result);
			Assert::AreEqual((uint32_t)1, decorator->executionCount);
			Assert::AreEqual((uint32_t)1, node->executionCount);
		}
	}

	TEST_METHOD(NodeDecorator_successSkipped) {
		MemoryGuard guard;
		{
			auto blackboard = makeIntrusive<Blackboard>();
			auto decorator = makeIntrusive<TestFailureDecorator>();
			auto node = makeIntrusive<TestSuccessNode>();
			node->decorators.add(decorator.get());

			auto result = node->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::FAILURE == result);
			Assert::AreEqual((uint32_t)1, decorator->executionCount);
			Assert::AreEqual((uint32_t)0, node->executionCount);
		}
	}

	TEST_METHOD(NodeDecorator_successBothFirstSkips) {
		MemoryGuard guard;
		{
			auto blackboard = makeIntrusive<Blackboard>();
			auto decorator1 = makeIntrusive<TestFailureDecorator>();
			auto decorator2 = makeIntrusive<TestExecuteDecorator>();
			auto node = makeIntrusive<TestSuccessNode>();
			node->decorators.add(decorator1.get());
			node->decorators.add(decorator2.get());

			auto result = node->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::FAILURE == result);
			Assert::AreEqual((uint32_t)1, decorator1->executionCount);
			Assert::AreEqual((uint32_t)0, decorator2->executionCount);
			Assert::AreEqual((uint32_t)0, node->executionCount);
		}
	}

	TEST_METHOD(NodeDecorator_successBothSecondSkips) {
		MemoryGuard guard;
		{
			auto blackboard = makeIntrusive<Blackboard>();
			auto decorator1 = makeIntrusive<TestExecuteDecorator>();
			auto decorator2 = makeIntrusive<TestFailureDecorator>();
			auto node = makeIntrusive<TestSuccessNode>();
			node->decorators.add(decorator1.get());
			node->decorators.add(decorator2.get());

			auto result = node->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::FAILURE == result);
			Assert::AreEqual((uint32_t)1, decorator1->executionCount);
			Assert::AreEqual((uint32_t)1, decorator2->executionCount);
			Assert::AreEqual((uint32_t)0, node->executionCount);
		}
	}

	TEST_METHOD(NodeDecorator_failureExecuted) {
		MemoryGuard guard;
		{
			auto blackboard = makeIntrusive<Blackboard>();
			auto decorator = makeIntrusive<TestExecuteDecorator>();
			auto node = makeIntrusive<TestFailureNode>();
			node->decorators.add(decorator.get());

			auto result = node->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::FAILURE == result);
			Assert::AreEqual((uint32_t)1, decorator->executionCount);
			Assert::AreEqual((uint32_t)1, node->executionCount);
		}
	}

	TEST_METHOD(NodeDecorator_failureSkipped) {
		MemoryGuard guard;
		{
			auto blackboard = makeIntrusive<Blackboard>();
			auto decorator = makeIntrusive<TestFailureDecorator>();
			auto node = makeIntrusive<TestFailureNode>();
			node->decorators.add(decorator.get());

			auto result = node->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::FAILURE == result);
			Assert::AreEqual((uint32_t)1, decorator->executionCount);
			Assert::AreEqual((uint32_t)0, node->executionCount);
		}
	}

	TEST_METHOD(NodeDecorator_inProgressExecuted) {
		MemoryGuard guard;
		{
			auto blackboard = makeIntrusive<Blackboard>();
			auto decorator = makeIntrusive<TestExecuteDecorator>();
			auto node = makeIntrusive<TestInProgressNode>(2);
			node->decorators.add(decorator.get());

			auto result = node->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::IN_PROGRESS == result);
			Assert::AreEqual((uint32_t)1, decorator->executionCount);
			Assert::AreEqual((uint32_t)1, node->executionCount);
			result = node->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::IN_PROGRESS == result);
			Assert::AreEqual((uint32_t)1, decorator->executionCount);
			Assert::AreEqual((uint32_t)2, node->executionCount);
			result = node->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::SUCCESS == result);
			Assert::AreEqual((uint32_t)1, decorator->executionCount);
			Assert::AreEqual((uint32_t)3, node->executionCount);
		}
	}
	};
}
