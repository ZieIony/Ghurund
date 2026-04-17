#include "ghe2dpch.h"
#include "SpriteComponent.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& SpriteComponent::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<SpriteComponent>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}
