#include "ghepch.h"
#include "SelectorNode.h"

namespace Ghurund::Engine {
	NodeExecutionResult SelectorNode::onExecute(Blackboard* blackboard) {
		for (size_t i = 0; i < children.Size; i++) {
			auto node = children[(currentIndex + i) % children.Size];
			auto result = node->execute(blackboard);
			if (result != NodeExecutionResult::FAILURE) {
				currentIndex = (currentIndex + i) % children.Size;
				return result;
			}
		}
		return NodeExecutionResult::FAILURE;
	}
}
