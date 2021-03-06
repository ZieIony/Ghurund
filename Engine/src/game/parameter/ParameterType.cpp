#include "ghpch.h"
#include "ParameterType.h"

#include "core/Pointer.h"

namespace Ghurund {
    using namespace DirectX;

    const ParameterType ParameterType::INT = ParameterType(ParameterTypeEnum::INT, _T("int"), sizeof(int));
    const ParameterType ParameterType::INT2 = ParameterType(ParameterTypeEnum::INT2, _T("int2"), sizeof(XMINT2));
    const ParameterType ParameterType::FLOAT = ParameterType(ParameterTypeEnum::FLOAT, _T("float"), sizeof(float));
    const ParameterType ParameterType::FLOAT2 = ParameterType(ParameterTypeEnum::FLOAT2, _T("float2"), sizeof(XMFLOAT2));
    const ParameterType ParameterType::FLOAT3 = ParameterType(ParameterTypeEnum::FLOAT3, _T("float3"), sizeof(XMFLOAT3));
    const ParameterType ParameterType::MATRIX = ParameterType(ParameterTypeEnum::MATRIX, _T("matrix"), sizeof(XMFLOAT4X4));
    const ParameterType ParameterType::COLOR = ParameterType(ParameterTypeEnum::COLOR, _T("color"), sizeof(XMFLOAT4));
    const ParameterType ParameterType::TEXTURE = ParameterType(ParameterTypeEnum::TEXTURE, _T("texture"), sizeof(Pointer*));

    const EnumValues<ParameterTypeEnum, ParameterType> ParameterType::VALUES = {
        &ParameterType::INT,
        &ParameterType::INT2,
        &ParameterType::FLOAT,
        &ParameterType::FLOAT2,
        &ParameterType::FLOAT3,
        &ParameterType::MATRIX,
        &ParameterType::COLOR,
        &ParameterType::TEXTURE
    };
}