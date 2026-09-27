#pragma once

#include "InputType.h"

#include "engine/graphics/texture/ITexture.h"

namespace Ghurund::Engine {
	class TextureConstant {
	private:
		const ITexture* value = nullptr;

	public:
		const AString name;
		const uint32_t bindSlot;

		TextureConstant(const AString& name, uint32_t bindSlot):name(name), bindSlot(bindSlot) {}

		~TextureConstant() {
			if (value)
				value->release();
		}

		inline const ITexture* getValue() {
			return value;
		}

		inline void setValue(const ITexture* value) {
			setPointer(this->value, value);
		}

		__declspec(property(get = getValue, put = setValue)) const ITexture* Value;
	};
}
