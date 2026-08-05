#include "ghepch.h"
#include "NodeDecorator.h"

namespace Ghurund::Engine {
	const Ghurund::Core::Type& NodeDecorator::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<NodeDecorator>()
			.withProperty(PROPERTY_NAME)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}
