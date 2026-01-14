#pragma once

#include "Parameter.h"

#include "core/reflection/StandardTypes.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class BaseValueParameter:public Parameter {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<BaseValueParameter>()
				.withSupertype(__super::GET_TYPE());

			return TYPE;
		}

		inline static const Ghurund::Core::Type& TYPE = BaseValueParameter::GET_TYPE();
#pragma endregion

	protected:
		void* rawValue = nullptr;	// initialize in ValueParameter

	protected:
		BaseValueParameter(const BaseValueParameter& other):Parameter(other) {}

	public:
		BaseValueParameter(const AString& constantName):Parameter(constantName) {}

		inline const void* const getRawValue() const {
			if (isEmpty)
				return nullptr;
			return rawValue;
		}

		__declspec(property(get = getRawValue)) const void* const RawValue;
	};

	template<typename T>
	class ValueParameter:public BaseValueParameter {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<ValueParameter>()
				.withSupertype(__super::GET_TYPE())
				.withTemplateParam<T>();

			return TYPE;
		}

		inline static const Ghurund::Core::Type& TYPE = ValueParameter::GET_TYPE();
#pragma endregion

	private:
		T value;

	protected:
		ValueParameter(const ValueParameter<T>& other):BaseValueParameter(other), value(other.value) {
			rawValue = &value;
		}

	public:
		using value_t = T;

		ValueParameter(const AString& constantName):BaseValueParameter(constantName), value(T()) {
			rawValue = &this->value;
		}

		ValueParameter(const AString& constantName, const T value):BaseValueParameter(constantName), value(value) {
			rawValue = &this->value;
			isEmpty = false;
		}

		inline T getValue() const {
			return value;
		}

		inline void setValue(const T& value) {
			this->value = value;
			isEmpty = false;
		}

		__declspec(property(get = getValue, put = setValue)) const T Value;

		inline size_t getSize() const {
			return SIZE;
		}

		__declspec(property(get = getSize)) size_t Size;

		static inline size_t SIZE = sizeof(T);

		virtual ValueParameter<T>* clone() const override {
			return ghnew ValueParameter<T>(*this);
		}
	};

	template<>
	class ValueParameter<bool>:public BaseValueParameter {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<ValueParameter>()
				.withSupertype(__super::GET_TYPE())
				.withTemplateParam<bool>();

			return TYPE;
		}

		inline static const Ghurund::Core::Type& TYPE = ValueParameter::GET_TYPE();
#pragma endregion

	private:
		float value;

	protected:
		ValueParameter(const ValueParameter<bool>& other):BaseValueParameter(other), value(other.value) {
			rawValue = &value;
		}

	public:
		using value_t = bool;

		ValueParameter(const AString& constantName):BaseValueParameter(constantName), value(0.0f) {
			rawValue = &this->value;
		}

		ValueParameter(const AString& constantName, const bool value):BaseValueParameter(constantName), value(value ? 1.0f : 0.0f) {
			rawValue = &this->value;
			isEmpty = false;
		}

		inline bool getValue() const {
			return value > 0.5f;
		}

		inline void setValue(const bool& value) {
			this->value = value ? 1.0f : 0.0f;
			isEmpty = false;
		}

		__declspec(property(get = getValue, put = setValue)) const bool Value;

		inline size_t getSize() const {
			return SIZE;
		}

		__declspec(property(get = getSize)) size_t Size;

		static inline size_t SIZE = sizeof(float);

		virtual ValueParameter<bool>* clone() const override {
			return ghnew ValueParameter<bool>(*this);
		}
	};

	typedef ValueParameter<bool> BoolParameter;
	typedef ValueParameter<float> FloatParameter;
	typedef ValueParameter<::DirectX::XMFLOAT2> Float2Parameter;
	typedef ValueParameter<::DirectX::XMFLOAT3> Float3Parameter;
	typedef ValueParameter<::DirectX::XMFLOAT4> Float4Parameter;
	typedef ValueParameter<int32_t> IntParameter;
	typedef ValueParameter<::DirectX::XMINT2> Int2Parameter;
	typedef ValueParameter<::DirectX::XMFLOAT4X4> MatrixParameter;
}