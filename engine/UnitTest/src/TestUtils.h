#pragma once

#include <initializer_list>

template<typename Value, typename Collection>
bool collectionContains(const Collection& collection, const std::initializer_list<Value>& list) {
    for (const Value& item : list) {
        if (!collection.contains(item))
            return false;
    }
    return true;
}

template<typename Collection, typename Collection2>
bool collectionContains(const Collection& collection, const Collection2& collection2) {
    for (const auto& item : collection2) {
        if (!collection.contains(item))
            return false;
    }
    return true;
}

template<typename Value, typename Collection>
bool collectionsEqual(const Collection& collection, const std::initializer_list<Value>& list) {
    const auto& iterator = collection.begin();
    const Value& iterator2 = list.begin();
    for (; iterator != collection.end(), iterator2 != list.end(); iterator++, iterator2++) {
        if (*iterator != *iterator2)
            return false;
    }
    return true;
}

template<typename Collection, typename Collection2>
bool collectionsEqual(const Collection& collection, const Collection2& collection2) {
    auto iterator = collection.begin();
    auto iterator2 = collection2.begin();
    for (; iterator != collection.end(), iterator2 != collection2.end(); ++iterator, ++iterator2) {
        if (*iterator != *iterator2)
            return false;
    }
    return true;
}