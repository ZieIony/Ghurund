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
	
	void AnimatedSpriteComponent::update(const XMFLOAT4X4& parentTransformation, const Timer& timer) {
		__super::update(parentTransformation, timer);
		if (animation) {
			animation->update(timer.ScaledFrameTime);
			if (material)
				inputs.ColorTexture = animation->CurrentTexture;
		}
	}
}
