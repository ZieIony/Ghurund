#pragma once

#include "Type.h"
#include "core/Buffer.h"
#include "core/math/Size.h"
#include "core/math/Matrix.h"
#include "core/string/String.h"

#include <DirectXMath.h>

namespace Ghurund::Core {

    template<>
    const Type& getType<void>();

    template<>
    const Type& getType<int32_t>();

    template<>
    const Type& getType<uint32_t>();

    template<>
    const Type& getType<float>();

    template<>
    const Type& getType<bool>();

    template<>
    const Type& getType<char>();

    template<>
    const Type& getType<AString>();

    template<>
    const Type& getType<WString>();

    template<>
    const Type& getType<IntSize>();

    template<>
    const Type& getType<FloatSize>();

    template<>
    const Type& getType<Matrix3x2>();

    template<>
    const Type& getType<Buffer>();

    template<>
    const Type& getType<DirectX::XMINT2>();

    template<>
    const Type& getType<DirectX::XMFLOAT2>();

    template<>
    const Type& getType<DirectX::XMFLOAT3>();

    template<>
    const Type& getType<DirectX::XMFLOAT4>();

    template<>
    const Type& getType<DirectX::XMFLOAT4X4>();
}