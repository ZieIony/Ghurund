#pragma once

#include "Common.h"

#include <algorithm>
#undef min
#undef max

namespace Ghurund {
    class Collection {
    protected:
        size_t initial;
        size_t size;
        size_t capacity;

    public:
        const static size_t INITIAL_CAPACITY = 10;

        Collection() {
            size = 0;
            capacity = initial = Collection::INITIAL_CAPACITY;
        }

        Collection(const Collection& collection) {
            size = collection.size;
            capacity = collection.capacity;
            initial = collection.initial;
        }

        Collection(Collection&& collection) noexcept {
            size = collection.size;
            capacity = collection.capacity;
            initial = collection.initial;
            collection.size = 0;
        }

        virtual ~Collection() = 0 {};

        inline void clear() {
            size = 0;
        }

        inline size_t getSize()const {
            return size;
        }

        __declspec(property(get = getSize)) size_t Size;

        inline bool isEmpty()const {
            return size == 0;
        }

        __declspec(property(get = isEmpty)) bool Empty;

        Collection& operator=(const Collection& other) {
            if (this == &other)
                return *this;
            size = other.size;
            initial = other.initial;
            capacity = other.capacity;
            return *this;
        }

        Collection& operator=(Collection&& other) noexcept {
            if (this == &other)
                return *this;
            size = other.size;
            initial = other.initial;
            capacity = other.capacity;
            other.size = 0;
            return *this;
        }
    };

}
