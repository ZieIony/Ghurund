#pragma once

#include "SpriteAnimation.h"
#include "SpriteAnimator.h"
#include <core/Timer.h>

namespace Ghurund::Engine::_2D {
	class AnimatedSpriteComponent {
	protected:
		SpriteAnimation* animation = nullptr;
		SpriteAnimator* animator = nullptr;

	public:
		~AnimatedSpriteComponent() {
			if (animation)
				animation->release();
			if (animator)
				animator->release();
		}

		inline SpriteAnimation* getAnimation() {
			return animation;
		}

		inline void setAnimation(SpriteAnimation* animation) {
			setPointer(this->animation, animation);
		}

		__declspec(property(get = getAnimation, put = setAnimation)) SpriteAnimation* Animation;

		inline SpriteAnimator* getAnimator() {
			return animator;
		}

		inline void setAnimator(SpriteAnimator* animator) {
			setPointer(this->animator, animator);
		}

		__declspec(property(get = getAnimator, put = setAnimator)) SpriteAnimator* Animator;

		void update(const Timer& timer);
	};
}
