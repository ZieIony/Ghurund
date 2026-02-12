#include "ghe2dpch.h"
#include "Component2DGroup.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& Component2DGroup::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<Component2DGroup>();

		static const Ghurund::Core::Type TYPE = TypeBuilder<Component2DGroup>()
			.withConstructor(CONSTRUCTOR)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}
