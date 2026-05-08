#pragma once

#include "BaseSpriteComponent.h"

#include "engine/graphics/texture/ITexture.h"

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;

	class SpriteComponent:public BaseSpriteComponent {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = SpriteComponent::GET_TYPE();
#pragma endregion

	protected:
		ITexture* colorTexture = nullptr;

	public:
		SpriteComponent(NotNull<Entity2D> owner, World2D& world):BaseSpriteComponent(owner, world) {}

		virtual ~SpriteComponent() {
			if (colorTexture)
				colorTexture->release();
		}

		inline void setColorTexture(ITexture* colorTexture) {
			setPointer(this->colorTexture, colorTexture);
		}

		__declspec(property(put = setColorTexture)) ITexture* ColorTexture;

		virtual void update(const Timer& timer) override {
			// TODO: don't update static parameters every frame (not only colorTexture)
			inputs.ColorTexture = colorTexture;
		}
	};
}