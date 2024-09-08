#pragma once

#include <type_traits>

namespace Ghurund::Core {
    template <class CollectionType, typename DataType>
    concept Iterable = requires(CollectionType collection) {
        { collection.begin() } -> std::same_as<typename CollectionType::iterator>;
        { *collection.begin() } -> std::same_as<DataType&>;
        { ((const CollectionType)collection).begin() } -> std::same_as<typename CollectionType::const_iterator>;
        { collection.end() } -> std::same_as<typename CollectionType::iterator>;
        { ((const CollectionType)collection).end() } -> std::same_as<typename CollectionType::const_iterator>;
    };
}