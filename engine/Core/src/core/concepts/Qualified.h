#pragma once

#include <type_traits>

namespace Ghurund::Core {
    template <class T>
    concept Qualified = std::is_const_v<T> || std::is_pointer_v<T> || std::is_reference_v<T> || std::is_volatile_v<T>;
}
