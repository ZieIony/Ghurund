#include "ghe2dpch.h"
#include "Component2D.h"

#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& Component2D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<Component2D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}