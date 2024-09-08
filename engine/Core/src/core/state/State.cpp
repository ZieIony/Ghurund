#include "ghcpch.h"
#include "State.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/StandardTypes.h"

namespace Ghurund::Core {
	template<>
	const Type& getType<State<bool>>() {
		static const Type TYPE = TypeBuilder<State<bool>>(NAMESPACE_NAME, GH_STRINGIFY(State<bool>)).withTemplateParam(getType<bool>());
		return TYPE;
	}
}