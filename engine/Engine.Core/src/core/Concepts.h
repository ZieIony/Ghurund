#pragma once

#include <type_traits>
#include <iterator>

namespace Ghurund {
    template <class T, class U>
    concept Derived = std::is_base_of<U, T>::value;

    template <class CollectionType>
    concept Iterable = requires(CollectionType collection) {
        { collection.begin() } -> std::forward_iterator;
        { collection.end() } -> std::forward_iterator;
    };
}