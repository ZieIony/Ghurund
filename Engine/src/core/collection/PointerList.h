#pragma once

#include "List.h"
#include "core/Pointer.h"

namespace Ghurund {
    template<class Value> class PointerList:public List<Value> {
    public:
        PointerList() {}

        ~PointerList() {
            for (size_t i = 0; i < List<Value>::size; i++)
                if (List<Value>::v[i] != nullptr)
                    List<Value>::v[i]->release();
        }

        inline void add(const Value& item) {
            if (item != nullptr)
                item->addReference();
            List<Value>::add(item);
        }


        inline void addAll(const List<Value>& list) {
            for (Value& item : list) {
                if (item != nullptr)
                    item->addReference();
            }
            List<Value>::addAll(list);
        }

        inline void addAll(const std::initializer_list<Value>& list) {
            for (Value& item : list) {
                if (item != nullptr)
                    item->addReference();
            }
            List<Value>::addAll(list);
        }

        inline void insert(size_t i, const Value& item) {
            List<Value>::insert(i, item);
            if (item != nullptr)
                item->addReference();
        }

        inline void set(size_t i, const Value& item) {
            if (List<Value>::v[i] != nullptr)
                List<Value>::v[i]->release();
            List<Value>::set(i, item);
            if (item != nullptr)
                item->addReference();
        }

        inline void removeAt(size_t i) {
            if (List<Value>::v[i] != nullptr)
                List<Value>::v[i]->release();
            List<Value>::removeAt(i);
        }

        inline void remove(const Value& item) {
            List<Value>::remove(item);
            if (item != nullptr)
                item->release();
        }

        inline void clear() {
            size_t s = List<Value>::size;
            List<Value>::clear();
            for (size_t i = 0; i < s; i++)
                if (List<Value>::v[i] != nullptr)
                    List<Value>::v[i]->release();
        }
    };
}
