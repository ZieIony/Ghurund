#pragma once

#include "SpriteAnimation.h"
#include "SpriteAnimator.h"

#include "core/time/Timer.h"
#include "engine/2d/graphics/sprite/SpriteRenderingSystem.h"

namespace Ghurund::Engine::_2D {
	class SpriteAnimationComponent {
	protected:
		SpriteAnimation* animation = nullptr;
		SpriteAnimator* animator = nullptr;

		virtual const Array<std::reference_wrapper<const Ghurund::Core::Type>>& getDependents_internal() const {
			static Array<std::reference_wrapper<const Ghurund::Core::Type>> dependents = { SpriteRenderingSystem::TYPE };
			return dependents;
		}

	public:
		~SpriteAnimationComponent() {
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

		inline void update(const Timer& timer) {
			if (animator) {
				animator->update();
				Animation = animator->CurrentState->Animation;
			}
			if (animation)
				animation->update(timer.FrameTime.scaledValue);
		}
	};
}
