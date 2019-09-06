#pragma once

#include "List.h"
#include "core/Pointer.h"

namespace Ghurund {
    template<class Value> class PointerList:public List<Value> {
    public:
        PointerList() {}

        ~PointerList() {
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

        inline void insertKeepOrder(size_t i, const Value& item) {
            List::insertKeepOrder(i, item);
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

        inline void removeAtKeepOrder(size_t i) {
            if (v[i] != nullptr)
                v[i]->release();
            List::removeAtKeepOrder(i);
        }

        inline void remove(const Value& item) {
            List::remove(item);
            if (item != nullptr)
                item->release();
        }

        inline void removeKeepOrder(const Value& item) {
            List::removeKeepOrder(item);
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