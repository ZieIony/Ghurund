#pragma once

#include <type_traits>

namespace Ghurund {
    template <class T, class U>
    concept Derived = std::is_base_of<U, T>::value;
}