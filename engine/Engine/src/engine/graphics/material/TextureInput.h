#pragma once

#include "MaterialInput.h"

#include "engine/graphics/shader/TextureConstant.h"

namespace Ghurund::Engine {
	class TextureInput:public MaterialInput {
	private:
		const ITexture* value;
		TextureConstant& shaderConstant;

	public:
		TextureInput(TextureConstant& shaderConstant):MaterialInput(true), value(nullptr), shaderConstant(shaderConstant) {}

		TextureInput(const TextureInput& other):MaterialInput(other), value(other.value), shaderConstant(other.shaderConstant) {
			if (value)
				value->addReference();
		}

		TextureInput(TextureInput&& other) noexcept:MaterialInput(other), value(other.value), shaderConstant(shaderConstant) {
			other.value = nullptr;
		}

		~TextureInput() {
			if (value)
				value->release();
		}

		const AString& getName() const {
			return shaderConstant.Name;
		}

		__declspec(property(get = getName)) const AString& Name;

		inline const ITexture* getValue() {
			return value;
		}

		inline void setValue(const ITexture* value) {
			setPointer(this->value, value);
			isEmpty = this->value == nullptr;
		}

		__declspec(property(get = getValue, put = setValue)) const ITexture* Value;

		virtual InputType getType() const override {
			return InputType::TEXTURE;
		}

		inline void applyValue() {
			shaderConstant.Value = value;
		}

		inline void applyValue(const ITexture* value) {
			shaderConstant.Value = value;
		}

		virtual TextureInput* clone() const override {
			return ghnew TextureInput(*this);
		}
	};
}