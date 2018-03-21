#pragma once

#include "Ghurund.h"
#include <algorithm>
#include "core/Object.h"

namespace Ghurund {
    template<class Key, class Value> class Collection:public Object {
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

        inline void set(Key i, Value e);
        inline Value get(Key i)const;
        inline void clear() {
            size = 0;
        }
        inline Value *begin();
        inline Value *end();
        inline size_t find(Value item);
        inline bool contains(Value item);
        Value &operator[](Key i);
        const Value &operator[](Key i)const;

        inline bool isEmpty()const {
            return size==0;
        }

        __declspec(property(get = isEmpty)) bool Empty;
    };

}
