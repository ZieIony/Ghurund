#pragma once

#include <compare>

namespace Ghurund::Core {
    template<size_t N>
    struct FixedString {
        char elems[N];

        constexpr FixedString(char const (&s)[N]) {
            std::copy_n(s, N, elems);
        }

        constexpr std::strong_ordering operator<=>(FixedString const&) const = default;
    };
}