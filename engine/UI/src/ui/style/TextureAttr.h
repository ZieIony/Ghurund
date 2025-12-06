#pragma once

#include "core/object/Object.h"
#include "engine/graphics/texture/ITexture.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI {
	class TextureAttr: public Ghurund::Core::Object {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = TextureAttr::GET_TYPE();
#pragma endregion

	public:
		virtual IntrusivePointer<ITexture> resolve(const Theme& theme) const = 0;
	};

	class TextureValue: public TextureAttr {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = TextureValue::GET_TYPE();
#pragma endregion

	private:
		IntrusivePointer<ITexture> texture;

	public:
		TextureValue(ITexture* texture):texture(texture) {
			if (texture)
				texture->addReference();
		}

		TextureValue(const TextureValue& other):texture(other.texture) {}

		TextureValue(TextureValue&& other) noexcept:texture(std::move(other.texture)) {}

		virtual IntrusivePointer<ITexture> resolve(const Theme& theme) const override {
			return texture;
		}

		TextureValue& operator=(const TextureValue& other) {
			texture = other.texture;
			return *this;
		}

		TextureValue& operator=(TextureValue&& other) noexcept {
			if (this == &other)
				return *this;
			texture = std::move(other.texture);
			return *this;
		}

		virtual TextureValue* clone() const override {
			return ghnew TextureValue(texture.get());
		}
	};

	class TextureRef: public TextureAttr {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = TextureRef::GET_TYPE();
#pragma endregion

	private:
		TextureKey key;

	public:
		TextureRef(TextureKey key):key(key) {}

		virtual IntrusivePointer<ITexture> resolve(const Theme& theme) const override;

		virtual TextureRef* clone() const override {
			return ghnew TextureRef(key);
		}
	};
}
