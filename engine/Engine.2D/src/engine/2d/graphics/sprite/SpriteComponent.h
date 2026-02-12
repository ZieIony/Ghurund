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

	private:
		inline void finalize() {
			safeRelease(colorTexture);
		}

	protected:
		ITexture* colorTexture = nullptr;

	public:
		SpriteComponent() {}

		SpriteComponent(NotNull<Ghurund::Engine::Mesh> mesh, NotNull<Ghurund::Engine::Material> material):BaseSpriteComponent(mesh, material) {}

		virtual ~SpriteComponent() {
			finalize();
		}

		virtual void invalidate() {
			finalize();
			__super::invalidate();
		}

		inline void setColorTexture(ITexture* colorTexture) {
			setPointer(this->colorTexture, colorTexture);
		}

		__declspec(property(put = setColorTexture)) ITexture* ColorTexture;

		virtual void update(const XMFLOAT4X4& parentTransformation, uint64_t time) override {
			__super::update(parentTransformation, time);
			// TODO: don't update static parameters every frame (not only colorTexture)
			inputs.ColorTexture = colorTexture;
		}
	};
}