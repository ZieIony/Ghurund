#pragma once

#include "core/string/String.h"

namespace Ghurund::Core {
    template<typename Result>
    inline Result parse(const AString& text) {
        return Result::parse(text);
    }
}