#pragma once

#include "Common.h"
#include "core/reflection/Type.h"

#include <compare>

namespace Ghurund::Core {
    struct IntPoint {
        int32_t x, y;

        auto operator<=>(const IntPoint& other) const = default;
    };

    struct FloatPoint {
        float x, y;

        auto operator<=>(const FloatPoint& other) const = default;
    };
}