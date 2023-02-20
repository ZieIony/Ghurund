#pragma once

#include <type_traits>
#include <iterator>
#include <memory>

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

    template <typename T> struct is_shared_ptr : std::false_type {};
    template <typename T> struct is_shared_ptr<std::shared_ptr<T>> : std::true_type {};

    template <typename T> concept IsSharedPtr = is_shared_ptr<T>::value;

    template <typename T> struct is_unique_ptr : std::false_type {};
    template <typename T> struct is_unique_ptr<std::unique_ptr<T>> : std::true_type {};

    template <typename T> concept IsUniquePtr = is_unique_ptr<T>::value;
}