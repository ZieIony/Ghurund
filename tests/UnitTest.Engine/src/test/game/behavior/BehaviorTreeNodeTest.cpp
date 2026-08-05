#include "utepch.h"
#include "CppUnitTest.h"

#include "TestNodes.h"
#include "TestDecorators.h"
#include "test/utils/MemoryGuard.h"
#include <core/object/IntrusivePointer.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	using namespace Ghurund::Core;
	using namespace Ghurund::Engine;
	using namespace UnitTest::Utils;

	TEST_CLASS(BehaviorTreeNode) {
public:

	TEST_METHOD(BehaviorTreeNode_abortSuccess) {
		MemoryGuard guard;
		{
			auto node = makeIntrusive<TestSuccessNode>();

			auto result = node->execute(nullptr);
			Assert::IsTrue(NodeExecutionResult::SUCCESS == result);
			Assert::IsFalse(node->IsExecutionInProgress);

			node->abort();
			Assert::AreEqual((uint32_t)0, node->abortCount);
			Assert::IsFalse(node->IsExecutionInProgress);
		}
	}

	TEST_METHOD(BehaviorTreeNode_abortInProgress) {
		MemoryGuard guard;
		{
			auto node = makeIntrusive<TestInProgressNode>(2);

			auto result = node->execute(nullptr);
			Assert::IsTrue(NodeExecutionResult::IN_PROGRESS == result);
			Assert::IsTrue(node->IsExecutionInProgress);

			node->abort();

			Assert::AreEqual((uint32_t)1, node->abortCount);
			Assert::IsFalse(node->IsExecutionInProgress);
		}
	}

	TEST_METHOD(BehaviorTreeNode_addDecorator) {
		MemoryGuard guard;
		{
			auto decorator = makeIntrusive<TestExecuteDecorator>();
			auto node = makeIntrusive<TestSuccessNode>();
			node->decorators.add(decorator.get());
		}
	}

	TEST_METHOD(BehaviorTreeNode_addRemoveDecorator) {
		MemoryGuard guard;
		{
			auto decorator = makeIntrusive<TestExecuteDecorator>();
			auto node = makeIntrusive<TestSuccessNode>();
			node->decorators.add(decorator.get());
			node->decorators.remove(decorator.get());
		}
	}
	};
}
