#pragma once

#include "BaseSpriteComponent.h"
#include "SpriteAnimation.h"

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

	public:
		AnimatedSpriteComponent(NotNull<Entity2D> owner, World2D& world):BaseSpriteComponent(owner, world) {}

		~AnimatedSpriteComponent() {
			if (animation)
				animation->release();
		}

		inline SpriteAnimation* getAnimation() {
			return animation;
		}

		inline void setAnimation(SpriteAnimation* animation) {
			setPointer(this->animation, animation);
		}

		__declspec(property(get = getAnimation, put = setAnimation)) SpriteAnimation* Animation;

		virtual void update(const XMFLOAT4X4& parentTransformation, const Timer& timer) override;
	};
}
