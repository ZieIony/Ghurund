#pragma once

#include <type_traits>

namespace Ghurund::Core {

    template <typename T>
    struct BaseType { typedef T type; };

    template <typename T>
    struct BaseType<const T>: public BaseType<T> {};

    template <typename T>
    struct BaseType<T*>: public BaseType<T> {};

    template <typename T>
    struct BaseType<const T*>: public BaseType<T> {};

    template <typename T>
    struct BaseType<volatile T>: public BaseType<T> {};

    template <typename T>
    struct BaseType<const volatile T>: public BaseType<T> {};

    template <typename T>
    struct BaseType<const volatile T*>: public BaseType<T> {};

    template <typename T>
    struct BaseType<T&>: public BaseType<T> {};

    template <typename T>
    struct BaseType<volatile T&>: public BaseType<T> {};

    template <typename T>
    struct BaseType<const volatile T&>: public BaseType<T> {};

    template <typename T>
    struct BaseType<T&&>: public BaseType<T> {};

}