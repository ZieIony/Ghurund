#pragma once

#include "core/string/String.h"

#include <stdint.h>
#include <compare>
#include <regex>

namespace Ghurund::Core {
    struct IntSize {
        uint32_t width, height;

        auto operator<=>(const IntSize& other) const = default;

        static IntSize parse(const AString& text);
    };

    template<>
    String toString(const IntSize& obj);

    struct FloatSize {
        float width, height;

        auto operator<=>(const FloatSize& other) const = default;

        static FloatSize parse(const AString& text);
    };

    template<>
    String toString(const FloatSize& obj);
}