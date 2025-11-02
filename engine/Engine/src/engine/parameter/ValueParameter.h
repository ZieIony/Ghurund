#pragma once

#include "Parameter.h"
#include "core/reflection/StandardTypes.h"

namespace Ghurund::Engine {

	template<typename T>
	class ValueParameter:public Parameter {
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

	public:
		using value_t = T;

		ValueParameter(const AString& constantName):Parameter(constantName), value(T()) {}

		ValueParameter(const AString& constantName, const T value):Parameter(constantName), value(value) {
			rawValue = &this->value;
			isEmpty = false;
		}

		inline T getValue() const {
			return value;
		}

		inline void setValue(const T& value) {
			this->value = value;
			rawValue = &this->value;
			isEmpty = false;
		}

		__declspec(property(get = getValue, put = setValue)) const T Value;

		inline void clearValue() {
			rawValue = nullptr;
			isEmpty = true;
		}

		virtual size_t getSize() const override {
			return SIZE;
		}

		static inline size_t SIZE = sizeof(T);
	};

	typedef ValueParameter<float> FloatParameter;
	typedef ValueParameter<::DirectX::XMFLOAT2> Float2Parameter;
	typedef ValueParameter<::DirectX::XMFLOAT3> Float3Parameter;
	typedef ValueParameter<::DirectX::XMFLOAT4> Float4Parameter;
	typedef ValueParameter<int32_t> IntParameter;
	typedef ValueParameter<::DirectX::XMINT2> Int2Parameter;
	typedef ValueParameter<::DirectX::XMFLOAT4X4> MatrixParameter;
}