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
		SpriteAnimation animation;

	public:
		AnimatedSpriteComponent() {}

		AnimatedSpriteComponent(NotNull<Ghurund::Engine::Mesh> mesh, NotNull<Ghurund::Engine::Material> material):BaseSpriteComponent(mesh, material) {}

		inline SpriteAnimation& getAnimation() {
			return animation;
		}

		__declspec(property(get = getAnimation)) SpriteAnimation& Animation;

		virtual bool isValid() const {
			return material != nullptr && material->Valid && mesh != nullptr && mesh->Valid;
		}

		virtual void update(const XMFLOAT4X4& parentTransformation, uint64_t time) override {
			__super::update(parentTransformation, time);
			animation.update(time);
			inputs.ColorTexture = animation.CurrentTexture;
		}
	};
}