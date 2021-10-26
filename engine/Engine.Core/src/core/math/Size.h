#pragma once

#include <stdint.h>
#include <compare>

namespace Ghurund::Core {
    struct IntSize {
        uint32_t width, height;

        auto operator<=>(const IntSize& other) const = default;
    };

    struct FloatSize {
        float width, height;

        auto operator<=>(const FloatSize& other) const = default;
    };
}