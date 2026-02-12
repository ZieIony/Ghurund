#include "ghe2dpch.h"
#include "SpriteComponent.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& SpriteComponent::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<SpriteComponent>();

		static const Ghurund::Core::Type TYPE = TypeBuilder<SpriteComponent>()
			.withConstructor(CONSTRUCTOR)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}
