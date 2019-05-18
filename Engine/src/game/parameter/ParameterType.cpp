#include "ParameterType.h"
#include "core/Pointer.h"

namespace Ghurund {

    const ParameterType& ParameterType::INT = ParameterType(ParameterTypeEnum::INT, sizeof(int));
    const ParameterType& ParameterType::INT2 = ParameterType(ParameterTypeEnum::INT2, sizeof(XMINT2));
    const ParameterType& ParameterType::FLOAT = ParameterType(ParameterTypeEnum::FLOAT, sizeof(float));
    const ParameterType& ParameterType::FLOAT2 = ParameterType(ParameterTypeEnum::FLOAT2, sizeof(XMFLOAT2));
    const ParameterType& ParameterType::FLOAT3 = ParameterType(ParameterTypeEnum::FLOAT3, sizeof(XMFLOAT3));
    const ParameterType& ParameterType::MATRIX = ParameterType(ParameterTypeEnum::MATRIX, sizeof(XMFLOAT4X4));
    const ParameterType& ParameterType::COLOR = ParameterType(ParameterTypeEnum::COLOR, sizeof(XMFLOAT4));
    const ParameterType& ParameterType::TEXTURE = ParameterType(ParameterTypeEnum::TEXTURE, sizeof(Pointer*));
}