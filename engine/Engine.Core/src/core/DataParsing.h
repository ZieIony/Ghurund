#pragma once

#include "core/string/String.h"

namespace Ghurund::Core {
    template<typename Result>
    inline Result parse(const AString& text) {
        return Result::parse(text);
    }

    template<>
    inline uint32_t parse(const AString& text) {
        return atoi(text.Data);
    }

    template<>
    inline int parse(const AString& text) {
        return atoi(text.Data);
    }

    template<>
    inline float parse(const AString& text) {
        return (float)atof(text.Data);
    }

    template<>
    inline double parse(const AString& text) {
        return atof(text.Data);
    }
}