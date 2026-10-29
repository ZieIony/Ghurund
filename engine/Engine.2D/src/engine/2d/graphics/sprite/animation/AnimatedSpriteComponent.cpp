#include "ghe2dpch.h"
#include "AnimatedSpriteComponent.h"

namespace Ghurund::Engine::_2D {
	void AnimatedSpriteComponent::update(const Timer& timer) {
		if (animator) {
			animator->update();
			Animation = animator->CurrentState->Animation;
		}
		if (animation)
			animation->update(timer.ScaledFrameTime);
	}
}
