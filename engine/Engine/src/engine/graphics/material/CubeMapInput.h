#pragma once

#include "MaterialInput.h"

#include "engine/graphics/shader/CubeMapConstant.h"

namespace Ghurund::Engine {
	class CubeMapInput:public MaterialInput {
	private:
		const ICubeMap* value;
		CubeMapConstant& shaderConstant;

	public:
		CubeMapInput(CubeMapConstant& shaderConstant):MaterialInput(true), value(nullptr), shaderConstant(shaderConstant) {}

		CubeMapInput(const CubeMapInput& other):MaterialInput(other), value(other.value), shaderConstant(other.shaderConstant) {
			if (value)
				value->addReference();
		}

		CubeMapInput(CubeMapInput&& other) noexcept:MaterialInput(other), value(other.value), shaderConstant(shaderConstant) {
			other.value = nullptr;
		}

		~CubeMapInput() {
			if (value)
				value->release();
		}

		const AString& getName() const {
			return shaderConstant.name;
		}

		__declspec(property(get = getName)) const AString& Name;

		inline const ICubeMap* getValue() {
			return value;
		}

		inline void setValue(const ICubeMap* value) {
			setPointer(this->value, value);
			isEmpty = this->value == nullptr;
		}

		__declspec(property(get = getValue, put = setValue)) const ICubeMap* Value;

		virtual InputType getType() const override {
			return InputType::CUBEMAP;
		}

		inline void applyValue() {
			shaderConstant.Value = value;
		}

		inline void applyValue(const ICubeMap* value) {
			shaderConstant.Value = value;
		}

		virtual CubeMapInput* clone() const override {
			return ghnew CubeMapInput(*this);
		}
	};
}
