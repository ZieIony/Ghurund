#include "ghepch.h"
#include "ValueInput.h"

#include "engine/parameter/ValueParameter.h"

namespace Ghurund::Engine {
	BaseValueParameter* ValueInput::makeParameter() const {
		switch (type) {
		case ValueInputType::INT:
			return makeParameter<IntParameter>();
		case ValueInputType::INT2:
			return makeParameter<Int2Parameter>();
		case ValueInputType::FLOAT:
			return makeParameter<FloatParameter>();
		case ValueInputType::FLOAT2:
			return makeParameter<Float2Parameter>();
		case ValueInputType::FLOAT3:
			return makeParameter<Float3Parameter>();
		case ValueInputType::FLOAT4:
			return makeParameter<Float4Parameter>();
		case ValueInputType::MATRIX:
			return makeParameter<MatrixParameter>();
		}
		throw InvalidParamException();
	}
}