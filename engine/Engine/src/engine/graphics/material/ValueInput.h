#pragma once

#include "MaterialInput.h"

#include "core/string/String.h"
#include "engine/graphics/shader/ValueConstant.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class BaseValueInput:public MaterialInput {
	protected:
		void* value;
		ValueConstant& shaderConstant;

	public:
		BaseValueInput(ValueConstant& shaderConstant):MaterialInput(true), value(ghnew int8_t[shaderConstant.Size]), shaderConstant(shaderConstant) {}

		BaseValueInput(const BaseValueInput& other):MaterialInput(other), value(ghnew int8_t[other.shaderConstant.Size]), shaderConstant(other.shaderConstant) {
			memcpy(value, other.value, other.shaderConstant.Size);
		}

		BaseValueInput(BaseValueInput&& other) noexcept:
			MaterialInput(other),
			value(other.value),
			shaderConstant(other.shaderConstant) {
			other.value = nullptr;
		}

		virtual ~BaseValueInput() = 0 {
			delete value;
		}

		inline const void* getRawValue() const {
			return isEmpty ? nullptr : value;
		}

		inline void setRawValue(const void* value) {
			if (value) {
				memcpy(this->value, value, shaderConstant.Size);
				isEmpty = false;
			} else {
				isEmpty = true;
			}
		}

		__declspec(property(get = getRawValue, put = setRawValue)) const void* RawValue;

		virtual const AString& getName() const override {
			return shaderConstant.Name;
		}

		virtual InputType getType() const override {
			return shaderConstant.Type;
		}

		inline const void* getDefaultValue() const {
			return shaderConstant.DefaultValue;
		}

		__declspec(property(get = getDefaultValue)) const void* DefaultValue;

		inline void applyValue() {
			shaderConstant.Value = value;
		}

		inline void applyValue(const void* value) {
			shaderConstant.Value = value;
		}
	};

	template<typename T>
	class ValueInput:public BaseValueInput {
	public:
		ValueInput(ValueConstant& shaderConstant):BaseValueInput(shaderConstant) {}

		ValueInput(const ValueInput& other):BaseValueInput(other) {}

		ValueInput(ValueInput&& other) noexcept:BaseValueInput(std::move(other)) {}

		inline const T& getValue() const {
			return *(T*)value;
		}

		inline void setValue(const T& value) {
			memcpy(this->value, &value, sizeof(T));
			isEmpty = false;
		}

		inline void setValue(nullptr_t) {
			isEmpty = true;
		}

		__declspec(property(get = getValue, put = setValue)) const T& Value;

		virtual ValueInput<T>* clone() const override {
			return ghnew ValueInput<T>(*this);
		}
	};

	typedef ValueInput<float> FloatInput;
	typedef ValueInput<::DirectX::XMFLOAT2> Float2Input;
	typedef ValueInput<::DirectX::XMFLOAT3> Float3Input;
	typedef ValueInput<::DirectX::XMFLOAT4> Float4Input;
	typedef ValueInput<int32_t> IntInput;
	typedef ValueInput<::DirectX::XMINT2> Int2Input;
	typedef ValueInput<::DirectX::XMFLOAT4X4> MatrixInput;
}