#include "ParameterType.h"
#include "core/Pointer.h"

namespace Ghurund {

    const ParameterType& ParameterType::INT = ParameterType(ParameterTypeValue::INT, sizeof(int));
    const ParameterType& ParameterType::INT2 = ParameterType(ParameterTypeValue::INT2, sizeof(XMINT2));
    const ParameterType& ParameterType::FLOAT = ParameterType(ParameterTypeValue::FLOAT, sizeof(float));
    const ParameterType& ParameterType::FLOAT2 = ParameterType(ParameterTypeValue::FLOAT2, sizeof(XMFLOAT2));
    const ParameterType& ParameterType::FLOAT3 = ParameterType(ParameterTypeValue::FLOAT3, sizeof(XMFLOAT3));
    const ParameterType& ParameterType::MATRIX = ParameterType(ParameterTypeValue::MATRIX, sizeof(XMFLOAT4X4));
    const ParameterType& ParameterType::COLOR = ParameterType(ParameterTypeValue::COLOR, sizeof(XMFLOAT4));
    const ParameterType& ParameterType::OBJECT = ParameterType(ParameterTypeValue::OBJECT, sizeof(Pointer*));
}