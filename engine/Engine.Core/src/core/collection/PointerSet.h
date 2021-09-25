#pragma once

#include "Set.h"
#include "core/Pointer.h"

namespace Ghurund::Core {
    template<class Value> class PointerSet :public Set<Value> {
    public:
        PointerSet() {}

        ~PointerSet() {
            for (size_t i = 0; i < size; i++)
                if (v[i] != nullptr)
                    v[i]->release();
        }

        inline void add(const Value& item) {
            if (item != nullptr)
                item->addReference();
            List::add(item);
        }

        inline void insert(size_t i, const Value& item) {
            List::insert(i, item);
            if (item != nullptr)
                item->addReference();
        }

        inline void set(size_t i, const Value& item) {
            if (v[i] != nullptr)
                v[i]->release();
            List::set(i, item);
            if (item != nullptr)
                item->addReference();
        }

        inline void removeAt(size_t i) {
            if (v[i] != nullptr)
                v[i]->release();
            List::removeAt(i);
        }

        inline void remove(const Value& item) {
            List::remove(item);
            if (item != nullptr)
                item->release();
        }

        inline void clear() {
            size_t s = size;
            List::clear();
            for (size_t i = 0; i < s; i++)
                if (v[i] != nullptr)
                    v[i]->release();
        }
    };
}