#pragma once

#include "Common.h"

namespace Ghurund::Core {
    class Collection {
    protected:
        size_t size;

    public:
        Collection() {
            size = 0;
        }

        Collection(const Collection& collection) {
            size = collection.size;
        }

        Collection(Collection&& collection) noexcept {
            size = collection.size;
            collection.size = 0;
        }

        virtual ~Collection()
        //    = 0   // TODO: a destructor cannot be abstract
        {};

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
            return *this;
        }

        Collection& operator=(Collection&& other) noexcept {
            if (this == &other)
                return *this;
            size = other.size;
            other.size = 0;
            return *this;
        }

        inline bool operator==(const Collection& other) const {
            if (this == &other)
                return true;
            return size == other.size;
        }

        inline bool operator!=(const Collection& other) const {
            return !(*this == other);
        }
    };
}
