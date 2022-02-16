#pragma once

#include <type_traits>
#include <iterator>

namespace Ghurund::Core {
    template <class T, class U>
    concept Derived = std::is_same_v<U, T> || std::is_base_of_v<U, T>;

    template <class T, class U>
    concept NotDerived = !std::is_same_v<U, T> && !std::is_base_of_v<U, T>;

    template <class T>
    concept Qualified = std::is_const_v<T> || std::is_pointer_v<T> || std::is_reference_v<T> || std::is_volatile_v<T>;

    template <class CollectionType>
    concept Iterable = requires(CollectionType collection) {
        { collection.begin() } -> std::forward_iterator;
        { collection.end() } -> std::forward_iterator;
    };
}