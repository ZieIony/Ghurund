#pragma once

#include "core/string/String.h"
#include "core/exception/Exceptions.h"

namespace Ghurund::Core {
    template<typename Result>
    inline Result parse(const AString& text) {
        return Result::parse(text);
    }

    template<>
    inline bool parse(const AString& text) {
        if (text == "true") {
            return true;
        } else if (text == "false") {
            return false;
        }
        throw InvalidFormatException();
    }
}
