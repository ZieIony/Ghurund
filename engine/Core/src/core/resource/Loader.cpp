#include "ghcpch.h"
#include "Loader.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {
	const Ghurund::Core::Type& Loader::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<Loader>(NAMESPACE_NAME, GH_STRINGIFY(Loader))
			.withModifiers(TypeModifier::ABSTRACT)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}