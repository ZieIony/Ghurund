#pragma once

#include "Collection.h"

#include <type_traits>

namespace Ghurund::Core {
    class CollectionWithCapacity:public Collection {
    protected:
        size_t initial;
        size_t capacity;

        const static size_t INITIAL_CAPACITY = 10;

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

        CollectionWithCapacity(CollectionWithCapacity&& other) noexcept:Collection(std::move(other)) {
            capacity = other.capacity;
            initial = other.initial;
            other.capacity = 0;
        }

        inline size_t getCapacity() const {
            return capacity;
        }

        __declspec(property(get = getCapacity)) size_t Capacity;

        CollectionWithCapacity& operator=(const CollectionWithCapacity& other) {
            if (this == &other)
                return *this;
            __super::operator=(other);
            initial = other.initial;
            capacity = other.capacity;
            return *this;
        }

        CollectionWithCapacity& operator=(CollectionWithCapacity&& other) noexcept {
            if (this == &other)
                return *this;
            __super::operator=(std::move(other));
            initial = other.initial;
            capacity = other.capacity;
            other.capacity = 0;
            return *this;
        }
    };

}
