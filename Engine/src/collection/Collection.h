#pragma once

#include "Common.h"
#include "TextUtils.h"
#include <algorithm>

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

        virtual ~Collection() {};

        inline void clear() {
            size = 0;
        }

        inline bool isEmpty()const {
            return size==0;
        }

        __declspec(property(get = isEmpty)) bool Empty;
    };

}
