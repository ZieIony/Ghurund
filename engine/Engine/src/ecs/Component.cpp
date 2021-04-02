#include "ghpch.h"
#include "Component.h"

namespace Ghurund {
	const Ghurund::Type& Component::GET_TYPE() {
		static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Component))
			.withModifiers(TypeModifier::ABSTRACT)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}
