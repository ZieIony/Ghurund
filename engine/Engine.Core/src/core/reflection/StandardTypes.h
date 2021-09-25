#pragma once

#include "Type.h"
#include "core/Buffer.h"
#include "core/math/Point.h"
#include "core/math/Size.h"
#include "core/math/Matrix3x2.h"
#include "core/string/String.h"

namespace Ghurund::Core {
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
    const Type& getType<FloatPoint>();

    template<>
    const Type& getType<IntPoint>();

    template<>
    const Type& getType<Matrix3x2>();

    template<>
    const Type& getType<Buffer>();
}