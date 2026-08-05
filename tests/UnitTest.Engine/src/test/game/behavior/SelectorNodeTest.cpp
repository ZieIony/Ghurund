#include "utepch.h"
#include "CppUnitTest.h"

#include "TestNodes.h"
#include "test/utils/MemoryGuard.h"
#include <engine/game/behavior/SelectorNode.h>
#include <core/object/IntrusivePointer.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	using namespace Ghurund::Engine;
	using namespace UnitTest::Utils;

	TEST_CLASS(SelectorNodeTest) {
public:
	TEST_METHOD(Behaviorselector_selectorSuccess) {
		MemoryGuard guard;
		{
			auto blackboard = makeIntrusive<Blackboard>();
			auto selector = makeIntrusive<SelectorNode>();
			auto node1 = makeIntrusive<TestSuccessNode>();
			auto node2 = makeIntrusive<TestSuccessNode>();
			selector->children.add(node1.get());
			selector->children.add(node2.get());

			auto result = selector->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::SUCCESS == result);
			Assert::IsTrue(node1.get() == selector->CurrentChild);
			Assert::AreEqual((uint32_t)1, node1->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);

			result = selector->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::SUCCESS == result);
			Assert::IsTrue(node1.get() == selector->CurrentChild);
			Assert::AreEqual((uint32_t)2, node1->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);
		}
	}

	TEST_METHOD(Behaviorselector_selectorFailure1) {
		MemoryGuard guard;
		{
			auto blackboard = makeIntrusive<Blackboard>();
			auto selector = makeIntrusive<SelectorNode>();
			auto node1 = makeIntrusive<TestFailureNode>();
			auto node2 = makeIntrusive<TestSuccessNode>();
			selector->children.add(node1.get());
			selector->children.add(node2.get());

			auto result = selector->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::SUCCESS == result);
			Assert::IsTrue(node2.get() == selector->CurrentChild);
			Assert::AreEqual((uint32_t)1, node1->executionCount);
			Assert::AreEqual((uint32_t)1, node2->executionCount);

			result = selector->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::SUCCESS == result);
			Assert::IsTrue(node2.get() == selector->CurrentChild);
			Assert::AreEqual((uint32_t)1, node1->executionCount);
			Assert::AreEqual((uint32_t)2, node2->executionCount);
		}
	}

	TEST_METHOD(Behaviorselector_selectorFailure2) {
		MemoryGuard guard;
		{
			auto blackboard = makeIntrusive<Blackboard>();
			auto selector = makeIntrusive<SelectorNode>();
			auto node1 = makeIntrusive<TestSuccessNode>();
			auto node2 = makeIntrusive<TestFailureNode>();
			selector->children.add(node1.get());
			selector->children.add(node2.get());

			auto result = selector->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::SUCCESS == result);
			Assert::IsTrue(node1.get() == selector->CurrentChild);
			Assert::AreEqual((uint32_t)1, node1->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);

			result = selector->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::SUCCESS == result);
			Assert::IsTrue(node1.get() == selector->CurrentChild);
			Assert::AreEqual((uint32_t)2, node1->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);
		}
	}

	TEST_METHOD(Behaviorselector_selectorFailureBoth) {
		MemoryGuard guard;
		{
			auto blackboard = makeIntrusive<Blackboard>();
			auto selector = makeIntrusive<SelectorNode>();
			auto node1 = makeIntrusive<TestFailureNode>();
			auto node2 = makeIntrusive<TestFailureNode>();
			selector->children.add(node1.get());
			selector->children.add(node2.get());

			auto result = selector->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::FAILURE == result);
			Assert::IsTrue(node1.get() == selector->CurrentChild);
			Assert::AreEqual((uint32_t)1, node1->executionCount);
			Assert::AreEqual((uint32_t)1, node2->executionCount);

			result = selector->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::FAILURE == result);
			Assert::IsTrue(node1.get() == selector->CurrentChild);
			Assert::AreEqual((uint32_t)2, node1->executionCount);
			Assert::AreEqual((uint32_t)2, node2->executionCount);
		}
	}

	TEST_METHOD(Behaviorselector_selectorInProgress) {
		MemoryGuard guard;
		{
			auto blackboard = makeIntrusive<Blackboard>();
			auto selector = makeIntrusive<SelectorNode>();
			auto node1 = makeIntrusive<TestInProgressNode>(2);
			auto node2 = makeIntrusive<TestInProgressNode>(2);
			selector->children.add(node1.get());
			selector->children.add(node2.get());

			auto result = selector->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::IN_PROGRESS == result);
			Assert::AreEqual((uint32_t)1, node1->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);
			result = selector->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::IN_PROGRESS == result);
			Assert::AreEqual((uint32_t)2, node1->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);
			result = selector->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::SUCCESS == result);
			Assert::AreEqual((uint32_t)3, node1->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);

			result = selector->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::IN_PROGRESS == result);
			Assert::AreEqual((uint32_t)4, node1->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);
			result = selector->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::IN_PROGRESS == result);
			Assert::AreEqual((uint32_t)5, node1->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);
			result = selector->execute(blackboard.get());
			Assert::IsTrue(NodeExecutionResult::SUCCESS == result);
			Assert::AreEqual((uint32_t)6, node1->executionCount);
			Assert::AreEqual((uint32_t)0, node2->executionCount);
		}
	}
	};
}
