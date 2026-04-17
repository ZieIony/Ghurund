#include "ghe2dpch.h"
#include "TransformComponent2D.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& TransformComponent2D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<TransformComponent2D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}
