#pragma once

#include <type_traits>

namespace Ghurund::Core {
    template <class T, class U>
    concept Derived = std::is_same_v<U, T> || std::is_base_of_v<U, T>;

    template <class T, class U>
    concept NotDerived = !std::is_same_v<U, T> && !std::is_base_of_v<U, T>;
}
