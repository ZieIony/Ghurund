#pragma once

#include "core/string/String.h"
#include "core/DataParsing.h"
#include "core/Exceptions.h"

#include <format>

namespace Ghurund::Core {
    template<>
    inline uint32_t parse(const AString& text) {
        uint32_t val;
        auto [p, ec] = std::from_chars(&text[0], &text[text.Length], val);
        if (ec != std::errc() || p != &text[text.Length])
            throw InvalidFormatException();
        return val;
    }

    template<>
    inline int parse(const AString& text) {
        int val;
        auto [p, ec] = std::from_chars(&text[0], &text[text.Length], val);
        if (ec != std::errc() || p != &text[text.Length])
            throw InvalidFormatException();
        return val;
    }
}