#pragma once

namespace Ghurund::Core {
    enum class LoadOption {
        DEFAULT = 0, DONT_WATCH = 1, DONT_CACHE = 2
    };

    LoadOption operator |(LoadOption lhs, LoadOption rhs);

    bool operator &(LoadOption lhs, LoadOption rhs);
}