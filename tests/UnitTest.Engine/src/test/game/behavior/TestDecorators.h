#pragma once

#include "engine/game/behavior/BehaviorTreeNode.h"

#include <cstdint>

namespace UnitTest {
	using namespace Ghurund::Engine;

	class TestExecuteDecorator:public NodeDecorator {
	protected:
		virtual bool shouldExecute(Blackboard* blackboard) override {
			executionCount++;
			return true;
		}

	public:
		uint32_t executionCount = 0;
	};

	class TestFailureDecorator:public NodeDecorator {
	protected:
		virtual bool shouldExecute(Blackboard* blackboard) override {
			executionCount++;
			return false;
		}

	public:
		uint32_t executionCount = 0;
	};
}
