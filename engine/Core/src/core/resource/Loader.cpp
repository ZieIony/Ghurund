#include "ghcpch.h"
#include "Loader.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {
	const Ghurund::Core::Type& Loader::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<Loader>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}