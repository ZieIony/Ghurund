#pragma once

#include "core/DataParsing.h"
#include "core/exception/Exceptions.h"
#include "core/string/String.h"

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
    inline int32_t parse(const AString& text) {
        int32_t val;
        auto [p, ec] = std::from_chars(&text[0], &text[text.Length], val);
        if (ec != std::errc() || p != &text[text.Length])
            throw InvalidFormatException();
        return val;
    }

    template<>
    inline uint16_t parse(const AString& text) {
        uint16_t val;
        auto [p, ec] = std::from_chars(&text[0], &text[text.Length], val);
        if (ec != std::errc() || p != &text[text.Length])
            throw InvalidFormatException();
        return val;
    }
}