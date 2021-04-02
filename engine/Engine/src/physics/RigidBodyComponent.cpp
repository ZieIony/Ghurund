#include "ghpch.h"
#include "RigidBodyComponent.h"

namespace Ghurund {
	const Ghurund::Type& Physics::RigidBodyComponent::GET_TYPE() {
		static const char* CLASS_NAME = GH_STRINGIFY(RigidBodyComponent);
		static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, CLASS_NAME)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}