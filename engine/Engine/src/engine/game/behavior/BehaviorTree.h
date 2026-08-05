#pragma once

#include "core/object/RefCountedObject.h"

#include "BehaviorTreeNode.h"
#include "Blackboard.h"

namespace Ghurund::Engine {
	class BehaviorTree:public RefCountedObject {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = BehaviorTree::GET_TYPE();
#pragma endregion

	private:
		Blackboard* blackboard;
		BehaviorTreeNode* root;

	public:
		inline Blackboard* getBlackboard() {
			return blackboard;
		}

		inline void setBlackboard(Blackboard* blackboard) {
			setPointer(this->blackboard, blackboard);
		}

		__declspec(property(get = getBlackboard, put = setBlackboard)) Blackboard* Blackboard;

		inline void setRoot(BehaviorTreeNode* node) {
			root = node;
		}

		inline BehaviorTreeNode* getRoot() {
			return root;
		}

		__declspec(property(get = getRoot, put = setRoot)) BehaviorTreeNode* Root;

		NodeExecutionResult execute() {
			return root->execute(blackboard);
		}
	};
}
