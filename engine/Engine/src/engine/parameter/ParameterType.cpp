#include "ghepch.h"
#include "ParameterType.h"

#include "core/object/RefCountedObject.h"

#include <DirectXMath.h>

namespace Ghurund::Engine {
    using namespace ::DirectX;

    const ParameterType ParameterType::INT = ParameterType(ParameterTypeEnum::INT, "INT", sizeof(int));
    const ParameterType ParameterType::INT2 = ParameterType(ParameterTypeEnum::INT2, "INT2", sizeof(XMINT2));
    const ParameterType ParameterType::FLOAT = ParameterType(ParameterTypeEnum::FLOAT, "FLOAT", sizeof(float));
    const ParameterType ParameterType::FLOAT2 = ParameterType(ParameterTypeEnum::FLOAT2, "FLOAT2", sizeof(XMFLOAT2));
    const ParameterType ParameterType::FLOAT3 = ParameterType(ParameterTypeEnum::FLOAT3, "FLOAT3", sizeof(XMFLOAT3));
    const ParameterType ParameterType::MATRIX = ParameterType(ParameterTypeEnum::MATRIX, "MATRIX", sizeof(XMFLOAT4X4));
    const ParameterType ParameterType::COLOR = ParameterType(ParameterTypeEnum::COLOR, "COLOR", sizeof(XMFLOAT4));
    const ParameterType ParameterType::TEXTURE = ParameterType(ParameterTypeEnum::TEXTURE, "TEXTURE", sizeof(RefCountedObject*));
}