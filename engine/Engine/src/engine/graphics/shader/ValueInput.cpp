#include "ghepch.h"
#include "ValueInput.h"

#include "engine/parameter/ValueParameter.h"

namespace Ghurund::Engine {
	BaseValueParameter* ValueInput::makeParameter() const {
		switch (type) {
		case InputType::INT:
			return makeParameter<IntParameter>();
		case InputType::INT2:
			return makeParameter<Int2Parameter>();
		case InputType::FLOAT:
			return makeParameter<FloatParameter>();
		case InputType::FLOAT2:
			return makeParameter<Float2Parameter>();
		case InputType::FLOAT3:
			return makeParameter<Float3Parameter>();
		case InputType::FLOAT4:
			return makeParameter<Float4Parameter>();
		case InputType::MATRIX:
			return makeParameter<MatrixParameter>();
		}
		throw InvalidParamException();
	}
}