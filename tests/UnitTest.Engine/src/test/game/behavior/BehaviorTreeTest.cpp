#include "utepch.h"
#include "CppUnitTest.h"

#include "engine/game/behavior/BehaviorTree.h"

#include "TestNodes.h"
#include "test/utils/MemoryGuard.h"
#include <engine/game/behavior/SequenceNode.h>
#include <engine/game/behavior/SelectorNode.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	using namespace Ghurund::Engine;
	using namespace UnitTest::Utils;

	TEST_CLASS(BehaviorTreeTest) {
public:

	TEST_METHOD(BehaviorTree_success) {
		MemoryGuard guard;
		{
			BehaviorTree tree;
			TestSuccessNode node;
			tree.Root = &node;

			auto result = tree.execute();
			Assert::IsTrue(NodeExecutionResult::SUCCESS == result);
			Assert::AreEqual((uint32_t)1, node.executionCount);
		}
	}

	TEST_METHOD(BehaviorTree_failure) {
		MemoryGuard guard;
		{
			BehaviorTree tree;
			TestFailureNode node;
			tree.Root = &node;

			auto result = tree.execute();
			Assert::IsTrue(NodeExecutionResult::FAILURE == result);
			Assert::AreEqual((uint32_t)1, node.executionCount);
		}
	}

	TEST_METHOD(BehaviorTree_inProgress) {
		MemoryGuard guard;
		{
			BehaviorTree tree;
			TestInProgressNode node(2);
			tree.Root = &node;

			auto result = tree.execute();
			Assert::IsTrue(NodeExecutionResult::IN_PROGRESS == result);
			Assert::AreEqual((uint32_t)1, node.executionCount);
			result = tree.execute();
			Assert::IsTrue(NodeExecutionResult::IN_PROGRESS == result);
			Assert::AreEqual((uint32_t)2, node.executionCount);
			result = tree.execute();
			Assert::IsTrue(NodeExecutionResult::SUCCESS == result);
			Assert::AreEqual((uint32_t)3, node.executionCount);
		}
	}
	};
}
