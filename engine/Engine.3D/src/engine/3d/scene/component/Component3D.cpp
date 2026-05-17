#include "ghe3dpch.h"
#include "Component3D.h"

#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"

namespace Ghurund::Engine::_3D {
	const Ghurund::Core::Type& Component3D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<Component3D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}
