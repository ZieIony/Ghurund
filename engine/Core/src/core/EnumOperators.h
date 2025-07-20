#pragma once

#include <type_traits>

namespace Ghurund::Core {
    template <class T>
    concept IsEnum = std::is_enum_v<T>;

    template<IsEnum T>
    inline T operator |(T lhs, T rhs) {
        return (T)((std::underlying_type_t<T>)lhs | (std::underlying_type_t<T>)rhs);
    }

    template<IsEnum T>
    inline T& operator |=(T& lhs, T rhs) {
        return lhs = (T)((std::underlying_type_t<T>)lhs | (std::underlying_type_t<T>)rhs);
    }

    template<IsEnum T>
    inline T operator &(T lhs, T rhs) {
        return (T)((std::underlying_type_t<T>)lhs & (std::underlying_type_t<T>)rhs);
    }
}