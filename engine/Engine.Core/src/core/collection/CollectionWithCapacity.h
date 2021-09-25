#pragma once

#include "Collection.h"

#include <type_traits>

namespace Ghurund::Core {
    class CollectionWithCapacity:public Collection {
    protected:
        size_t initial;
        size_t capacity;

        const static size_t INITIAL_CAPACITY = 10;

        inline bool operator==(const CollectionWithCapacity& other) const {
            if (this->__super::operator!=(other))
                return false;
            return initial == other.initial || capacity == other.capacity;
        }

        inline bool operator!=(const CollectionWithCapacity& other) const {
            return !(*this == other);
        }

    public:
        CollectionWithCapacity() {
            capacity = initial = CollectionWithCapacity::INITIAL_CAPACITY;
        }

        CollectionWithCapacity(size_t capacity) {
            this->capacity = initial = capacity;
        }

        CollectionWithCapacity(const CollectionWithCapacity& collection):Collection(collection) {
            capacity = collection.capacity;
            initial = collection.initial;
        }

        CollectionWithCapacity(CollectionWithCapacity&& collection) noexcept:Collection(std::move(collection)) {
            capacity = collection.capacity;
            initial = collection.initial;
        }

        inline size_t getCapacity() const {
            return capacity;
        }

        __declspec(property(get = getCapacity)) size_t Capacity;
    };

}
