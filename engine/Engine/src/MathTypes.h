#pragma once

#include "core/reflection/Type.h"

#include <DirectXMath.h>

namespace Ghurund::Core {
    template<>
    const Type& getType<DirectX::XMFLOAT2>();

    template<>
    const Type& getType<DirectX::XMFLOAT3>();

    template<>
    const Type& getType<DirectX::XMFLOAT4>();
}