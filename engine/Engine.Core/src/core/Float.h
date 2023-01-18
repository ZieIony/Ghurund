#pragma once

#include "core/DataParsing.h"
#include "core/Exceptions.h"

#include <format>

namespace Ghurund::Core {
    template<>
    inline float parse(const AString& text) {
        float val;
        auto [p, ec] = std::from_chars(text.begin(), text.end() - 1, val);
        if (ec != std::errc() || p != text.end() - 1)
            throw InvalidFormatException();
        return val;
    }

    template<>
    inline double parse(const AString& text) {
        double val;
        auto [p, ec] = std::from_chars(text.begin(), text.end() - 1, val);
        if (ec != std::errc() || p != text.end() - 1)
            throw InvalidFormatException();
        return val;
    }
}