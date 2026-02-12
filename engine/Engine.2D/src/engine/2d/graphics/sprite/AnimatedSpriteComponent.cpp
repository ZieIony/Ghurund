#include "ghe2dpch.h"
#include "AnimatedSpriteComponent.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& AnimatedSpriteComponent::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<AnimatedSpriteComponent>();

		static const Ghurund::Core::Type TYPE = TypeBuilder<AnimatedSpriteComponent>()
			.withConstructor(CONSTRUCTOR)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}
