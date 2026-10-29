#include "ghe3dpch.h"
#include "Entity3D.h"

namespace Ghurund::Engine::_3D {
	const Ghurund::Core::Type& Entity3D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<Entity3D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}
