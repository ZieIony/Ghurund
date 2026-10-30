#include "ghe2dpch.h"
#include "SpriteAnimationComponent.h"

namespace Ghurund::Engine::_2D {
	void SpriteAnimationComponent::update(const Timer& timer) {
		if (animator) {
			animator->update();
			Animation = animator->CurrentState->Animation;
		}
		if (animation)
			animation->update(timer.ScaledFrameTime);
	}
}
