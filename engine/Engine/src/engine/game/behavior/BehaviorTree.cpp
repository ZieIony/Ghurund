#include "ghepch.h"
#include "BehaviorTree.h"

namespace Ghurund::Engine {
	const Ghurund::Core::Type& BehaviorTree::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<BehaviorTree>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}
