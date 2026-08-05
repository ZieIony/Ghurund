#pragma once

#include "engine/game/behavior/BehaviorTreeNode.h"

#include <cstdint>

namespace UnitTest {
	using namespace Ghurund::Engine;

	class TestSuccessNode:public BehaviorTreeNode {
	protected:
		virtual NodeExecutionResult onExecute(Blackboard* blackboard) override {
			executionCount++;
			return NodeExecutionResult::SUCCESS;
		}

		virtual void onAbort() override {
			abortCount++;
		}

	public:
		uint32_t executionCount = 0, abortCount = 0;
	};

	class TestFailureNode:public BehaviorTreeNode {
	protected:
		virtual NodeExecutionResult onExecute(Blackboard* blackboard) override {
			executionCount++;
			return NodeExecutionResult::FAILURE;
		}

		virtual void onAbort() override {
			abortCount++;
		}

	public:
		uint32_t executionCount = 0, abortCount = 0;
	};

	class TestInProgressNode:public BehaviorTreeNode {
	private:
		uint32_t inProgressTicks, currentTicks = 0;

	protected:
		virtual NodeExecutionResult onExecute(Blackboard* blackboard) override {
			executionCount++;
			if (currentTicks < inProgressTicks) {
				currentTicks++;
				return NodeExecutionResult::IN_PROGRESS;
			} else {
				currentTicks = 0;
				return NodeExecutionResult::SUCCESS;
			}
		}

		virtual void onAbort() override {
			abortCount++;
		}

	public:
		uint32_t executionCount = 0, abortCount = 0;

		TestInProgressNode(uint32_t inProgressTicks):inProgressTicks(inProgressTicks) {}
	};
}
