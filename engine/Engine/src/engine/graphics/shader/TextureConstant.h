#pragma once

#include "engine/graphics/texture/ITexture.h"

namespace Ghurund::Engine {
	class TextureConstant {
	private:
		const AString name;
		const ITexture* value = nullptr;

	public:
		TextureConstant(const AString& name):name(name) {}

		~TextureConstant() {
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

		inline void setValue(const ITexture* value) {
			setPointer(this->value, value);
		}

		__declspec(property(get = getValue, put = setValue)) const ITexture* Value;
	};
}