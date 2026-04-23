#pragma once

#include "BaseSpriteComponent.h"
#include "SpriteAnimation.h"
#include "SpriteAnimator.h"

namespace Ghurund::Engine::_2D {
	class AnimatedSpriteComponent:public BaseSpriteComponent {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = AnimatedSpriteComponent::GET_TYPE();
#pragma endregion

	protected:
		SpriteAnimation* animation = nullptr;
		SpriteAnimator* animator = nullptr;

	public:
		AnimatedSpriteComponent(NotNull<Entity2D> owner, World2D& world):BaseSpriteComponent(owner, world) {}

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

		virtual void update(const XMFLOAT4X4& parentTransformation, const Timer& timer) override;
	};
}
