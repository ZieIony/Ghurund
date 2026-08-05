#pragma once

#include "Blackboard.h"
#include "NodeDecorator.h"

#include "core/object/RefCountedObject.h"
#include "core/object/NamedObject.h"
#include "engine/game/NamedIntrusiveOrderedObservableCollection.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	enum class NodeExecutionResult {
		SUCCESS, FAILURE, IN_PROGRESS
	};

	class BehaviorTreeNode:public RefCountedObject, public AStringNamedObject {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = BehaviorTreeNode::GET_TYPE();
#pragma endregion

	private:
		bool executionInProgress = false;

	protected:
		virtual NodeExecutionResult onExecute(Blackboard* blackboard) {
			return NodeExecutionResult::SUCCESS;
		}

		virtual void onAbort() {}

	public:
		NamedIntrusiveOrderedObservableCollection<NodeDecorator> decorators;

		BehaviorTreeNode() {
			decorators.collectionChanged += [this](auto& sender) {
				abort();
			};
		}

		virtual ~BehaviorTreeNode() = 0 {}

		inline NodeExecutionResult execute(Blackboard* blackboard) {
			if (!executionInProgress) {
				for (auto decorator : decorators) {
					if (!decorator->shouldExecute(blackboard))
						return NodeExecutionResult::FAILURE;
				}
			}

			auto result = onExecute(blackboard);
			executionInProgress = result == NodeExecutionResult::IN_PROGRESS;
			return result;
		}

		inline bool getIsExecutionInProgress() const {
			return executionInProgress;
		}

		__declspec(property(get = getIsExecutionInProgress)) bool IsExecutionInProgress;

		inline void abort() {
			if (!executionInProgress)
				return;
			onAbort();
			executionInProgress = false;
		}
	};
}
