#pragma once

#include "BehaviorTreeNode.h"

#include "engine/game/NamedIntrusiveOrderedObservableCollection.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class SelectorNode:public BehaviorTreeNode {
	private:
		size_t currentIndex = 0;

	protected:
		virtual NodeExecutionResult onExecute(Blackboard* blackboard) override;

		virtual void onAbort() {
			children[currentIndex]->abort();
			currentIndex = 0;
		}

	public:
		NamedIntrusiveOrderedObservableCollection<BehaviorTreeNode> children;

		SelectorNode() {
			children.collectionChanged += [this](auto& sender) {
				abort();
			};
		}

		inline BehaviorTreeNode* getCurrentChild() {
			return children[currentIndex];
		}

		__declspec(property(get = getCurrentChild)) BehaviorTreeNode* CurrentChild;
	};
}
