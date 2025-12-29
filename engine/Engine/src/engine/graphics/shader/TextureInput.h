#pragma once

#include "engine/graphics/texture/ITexture.h"

namespace Ghurund::Engine {
	class TextureParameter;

	class TextureInput {
	private:
		const AString name;
		const ITexture* value = nullptr;

	public:
		TextureInput(const AString& name):name(name) {}

		~TextureInput() {
			if (value)
				value->release();
		}

		const AString& getName() const {
			return name;
		}

		__declspec(property(get = getName)) const AString& Name;

		inline const ITexture* getValue() {
			return value;
		}

		void setValue(const ITexture* value) {
			setPointer(this->value, value);
		}

		void clearValue() {
			if (value) {
				value->release();
				value = nullptr;
			}
		}

		__declspec(property(get = getValue, put = setValue)) const ITexture* Value;

		TextureParameter* makeParameter() const;
	};
}