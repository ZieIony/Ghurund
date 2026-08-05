#include "utepch.h"
#include "CppUnitTest.h"

#include "test/utils/MemoryGuard.h"
#include "TestDecorators.h"
#include "TestNodes.h"
#include <core/object/IntrusivePointer.h>
#include <engine/game/behavior/SequenceNode.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	using namespace Ghurund::Engine;
	using namespace UnitTest::Utils;

	TEST_CLASS(SequenceNodeTest) {
public:

	TEST_METHOD(SequenceNode_success) {
		MemoryGuard guard;
		{
			auto blackboard = makeIntrusive<Blackboard>();
			auto sequence = makeIntrusive<SequenceNode>();
			auto node1 = makeIntrusive<TestSuccessNode>();
			auto node2 = makeIntrusive<TestSuccessNode>();
			sequence->children.add(node1.get());
			sequence->children.add(node2.get());

			auto result = sequence->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::SUCCESS == result);
			Assert::IsTrue(node2.get() == sequence->CurrentChild);
			Assert::AreEqual((uint32_t)1, node1->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);

			result = sequence->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::SUCCESS == result);
			Assert::IsTrue(node1.get() == sequence->CurrentChild);
			Assert::AreEqual((uint32_t)1, node1->executionCount);
			Assert::AreEqual((uint32_t)1, node2->executionCount);
		}
	}

	TEST_METHOD(SequenceNode_successFailureDecorator1) {
		MemoryGuard guard;
		{
			auto blackboard = makeIntrusive<Blackboard>();
			auto sequence = makeIntrusive<SequenceNode>();
			auto decorator = makeIntrusive<TestFailureDecorator>();
			auto node1 = makeIntrusive<TestSuccessNode>();
			auto node2 = makeIntrusive<TestSuccessNode>();
			node1->decorators.add(decorator.get());
			sequence->children.add(node1.get());
			sequence->children.add(node2.get());

			auto result = sequence->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::FAILURE == result);
			Assert::IsTrue(node1.get() == sequence->CurrentChild);
			Assert::AreEqual((uint32_t)1, decorator->executionCount);
			Assert::AreEqual((uint32_t)0, node1->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);

			result = sequence->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::FAILURE == result);
			Assert::IsTrue(node1.get() == sequence->CurrentChild);
			Assert::AreEqual((uint32_t)2, decorator->executionCount);
			Assert::AreEqual((uint32_t)0, node1->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);
		}
	}

	TEST_METHOD(SequenceNode_successFailureDecorator2) {
		MemoryGuard guard;
		{
			auto blackboard = makeIntrusive<Blackboard>();
			auto sequence = makeIntrusive<SequenceNode>();
			auto decorator = makeIntrusive<TestFailureDecorator>();
			auto node1 = makeIntrusive<TestSuccessNode>();
			auto node2 = makeIntrusive<TestSuccessNode>();
			sequence->children.add(node1.get());
			node2->decorators.add(decorator.get());
			sequence->children.add(node2.get());

			auto result = sequence->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::SUCCESS == result);
			Assert::IsTrue(node2.get() == sequence->CurrentChild);
			Assert::AreEqual((uint32_t)1, node1->executionCount);
			Assert::AreEqual((uint32_t)0, decorator->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);

			result = sequence->execute(blackboard.get());
			// TODO: is it ok that the entire sequence gets skipped and it still reports success?
			Assert::IsTrue(NodeExecutionResult::FAILURE == result);
			Assert::IsTrue(node1.get() == sequence->CurrentChild);
			Assert::AreEqual((uint32_t)1, node1->executionCount);
			Assert::AreEqual((uint32_t)1, decorator->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);
		}
	}

	TEST_METHOD(SequenceNode_sequenceFailure1) {
		MemoryGuard guard;
		{
			auto blackboard = makeIntrusive<Blackboard>();
			auto sequence = makeIntrusive<SequenceNode>();
			auto node1 = makeIntrusive<TestFailureNode>();
			auto node2 = makeIntrusive<TestSuccessNode>();
			sequence->children.add(node1.get());
			sequence->children.add(node2.get());

			auto result = sequence->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::FAILURE == result);
			Assert::IsTrue(node1.get() == sequence->CurrentChild);
			Assert::AreEqual((uint32_t)1, node1->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);

			result = sequence->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::FAILURE == result);
			Assert::IsTrue(node1.get() == sequence->CurrentChild);
			Assert::AreEqual((uint32_t)2, node1->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);
		}
	}

	TEST_METHOD(SequenceNode_sequenceFailure2) {
		MemoryGuard guard;
		{
			auto blackboard = makeIntrusive<Blackboard>();
			auto sequence = makeIntrusive<SequenceNode>();
			auto node1 = makeIntrusive<TestSuccessNode>();
			auto node2 = makeIntrusive<TestFailureNode>();
			sequence->children.add(node1.get());
			sequence->children.add(node2.get());

			auto result = sequence->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::SUCCESS == result);
			Assert::IsTrue(node2.get() == sequence->CurrentChild);
			Assert::AreEqual((uint32_t)1, node1->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);

			result = sequence->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::FAILURE == result);
			Assert::IsTrue(node1.get() == sequence->CurrentChild);
			Assert::AreEqual((uint32_t)1, node1->executionCount);
			Assert::AreEqual((uint32_t)1, node2->executionCount);
		}
	}

	TEST_METHOD(SequenceNode_sequenceFailureBoth) {
		MemoryGuard guard;
		{
			auto blackboard = makeIntrusive<Blackboard>();
			auto sequence = makeIntrusive<SequenceNode>();
			auto node1 = makeIntrusive<TestFailureNode>();
			auto node2 = makeIntrusive<TestFailureNode>();
			sequence->children.add(node1.get());
			sequence->children.add(node2.get());

			auto result = sequence->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::FAILURE == result);
			Assert::IsTrue(node1.get() == sequence->CurrentChild);
			Assert::AreEqual((uint32_t)1, node1->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);

			result = sequence->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::FAILURE == result);
			Assert::IsTrue(node1.get() == sequence->CurrentChild);
			Assert::AreEqual((uint32_t)2, node1->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);
		}
	}

	TEST_METHOD(SequenceNode_sequenceInProgress) {
		MemoryGuard guard;
		{
			auto blackboard = makeIntrusive<Blackboard>();
			auto sequence = makeIntrusive<SequenceNode>();
			auto node1 = makeIntrusive<TestInProgressNode>(2);
			auto node2 = makeIntrusive<TestInProgressNode>(2);
			sequence->children.add(node1.get());
			sequence->children.add(node2.get());

			auto result = sequence->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::IN_PROGRESS == result);
			Assert::IsTrue(node1.get() == sequence->CurrentChild);
			Assert::AreEqual((uint32_t)1, node1->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);
			result = sequence->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::IN_PROGRESS == result);
			Assert::IsTrue(node1.get() == sequence->CurrentChild);
			Assert::AreEqual((uint32_t)2, node1->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);
			result = sequence->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::SUCCESS == result);
			Assert::IsTrue(node2.get() == sequence->CurrentChild);
			Assert::AreEqual((uint32_t)3, node1->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);

			result = sequence->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::IN_PROGRESS == result);
			Assert::IsTrue(node2.get() == sequence->CurrentChild);
			Assert::AreEqual((uint32_t)3, node1->executionCount);
			Assert::AreEqual((uint32_t)1, node2->executionCount);
			result = sequence->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::IN_PROGRESS == result);
			Assert::IsTrue(node2.get() == sequence->CurrentChild);
			Assert::AreEqual((uint32_t)3, node1->executionCount);
			Assert::AreEqual((uint32_t)2, node2->executionCount);
			result = sequence->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::SUCCESS == result);
			Assert::IsTrue(node1.get() == sequence->CurrentChild);
			Assert::AreEqual((uint32_t)3, node1->executionCount);
			Assert::AreEqual((uint32_t)3, node2->executionCount);
		}
	}
	};
}
