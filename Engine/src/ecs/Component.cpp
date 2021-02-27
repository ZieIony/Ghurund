#include "Component.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund {
	const Ghurund::Type& Component::GET_TYPE() {
		static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Component))
			.withModifiers(TypeModifier::ABSTRACT)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}
