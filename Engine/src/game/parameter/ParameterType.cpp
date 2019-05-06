#include "ParameterType.h"
#include "core/Pointer.h"

namespace Ghurund {

    const ParameterValueType& ParameterValueType::INT = ParameterValueType(ParameterValueTypeValue::INT, sizeof(int));
    const ParameterValueType& ParameterValueType::INT2 = ParameterValueType(ParameterValueTypeValue::INT2, sizeof(XMINT2));
    const ParameterValueType& ParameterValueType::FLOAT = ParameterValueType(ParameterValueTypeValue::FLOAT, sizeof(float));
    const ParameterValueType& ParameterValueType::FLOAT2 = ParameterValueType(ParameterValueTypeValue::FLOAT2, sizeof(XMFLOAT2));
    const ParameterValueType& ParameterValueType::FLOAT3 = ParameterValueType(ParameterValueTypeValue::FLOAT3, sizeof(XMFLOAT3));
    const ParameterValueType& ParameterValueType::MATRIX = ParameterValueType(ParameterValueTypeValue::MATRIX, sizeof(XMFLOAT4X4));
    const ParameterValueType& ParameterValueType::COLOR = ParameterValueType(ParameterValueTypeValue::COLOR, sizeof(XMFLOAT4));
    const ParameterValueType& ParameterValueType::TEXTURE = ParameterValueType(ParameterValueTypeValue::TEXTURE, sizeof(Pointer*));
}