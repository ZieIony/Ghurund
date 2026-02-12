#include "ghe2dpch.h"
#include "TransformComponent2D.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& TransformComponent2D::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<TransformComponent2D>();

		static const Ghurund::Core::Type TYPE = TypeBuilder<TransformComponent2D>()
			.withConstructor(CONSTRUCTOR)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}
