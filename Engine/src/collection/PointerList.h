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
#ifdef _DEBUG
            assert(item != nullptr);
#endif
            item->addReference();
            List::add(item);
        }

        inline void insert(size_t i, const Value& item) {
#ifdef _DEBUG
            assert(item != nullptr);
#endif
            List::insert(i, item);
            item->addReference();
        }

        inline void insertKeepOrder(size_t i, const Value& item) {
#ifdef _DEBUG
            assert(item != nullptr);
#endif
            List::insertKeepOrder(i, item);
            item->addReference();
        }

        inline void set(size_t i, const Value& item) {
#ifdef _DEBUG
            assert(item != nullptr);
#endif
            v[i]->release();
            List::set(i, item);
            item->addReference();
        }

        inline void removeAt(size_t i) {
            v[i]->release();
            List::removeAt(i);
        }

        inline void removeAtKeepOrder(size_t i) {
            v[i]->release();
            List::removeAtKeepOrder(i);
        }

        inline void remove(const Value& item) {
#ifdef _DEBUG
            assert(item != nullptr);
#endif
            List::remove(item);
            item->release();
        }

        inline void removeKeepOrder(const Value& item) {
#ifdef _DEBUG
            assert(item != nullptr);
#endif
            List::removeKeepOrder(item);
            item->release();
        }

        inline void clear() {
            size_t s = size;
            List::clear();
            for (size_t i = 0; i < s; i++)
                v[i]->release();
        }
    };
}