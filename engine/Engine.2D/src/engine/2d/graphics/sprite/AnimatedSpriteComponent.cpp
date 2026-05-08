#include "ghe2dpch.h"
#include "AnimatedSpriteComponent.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& AnimatedSpriteComponent::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<AnimatedSpriteComponent>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
	
	void AnimatedSpriteComponent::update(const Timer& timer) {
		if (animator) {
			animator->update();
			Animation = animator->CurrentState->Animation;
		}
		if (animation) {
			animation->update(timer.ScaledFrameTime);
			if (material)
				inputs.ColorTexture = animation->CurrentTexture;
		}
	}
}
