#include "ghepch.h"
#include "BehaviorTreeNode.h"

namespace Ghurund::Engine {
	const Ghurund::Core::Type& BehaviorTreeNode::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<BehaviorTreeNode>()
			.withProperty(PROPERTY_NAME)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}
