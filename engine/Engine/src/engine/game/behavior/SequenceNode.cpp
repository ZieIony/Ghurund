#include "ghepch.h"
#include "SequenceNode.h"

namespace Ghurund::Engine {
	NodeExecutionResult SequenceNode::onExecute(Blackboard* blackboard) {
		auto node = children[currentIndex];
		auto result = node->execute(blackboard);
		if (result == NodeExecutionResult::SUCCESS) {
			currentIndex = (currentIndex + 1) % children.Size;
		} else if (result == NodeExecutionResult::FAILURE) {
			currentIndex = 0;
		}
		return result;
	}
}
