#pragma once

#include "List.h"
#include "core/Pointer.h"
#include "core/Event.h"

namespace Ghurund::Core {
    template<class Value> class ObservablePointerList:public PointerList<Value> {
    public:
        Event<ObservablePointerList<Value>, size_t> itemAdded = *this;
        Event<ObservablePointerList<Value>, size_t> itemRemoved = *this;

        inline void add(const Value& item) {
            PointerList<Value>::add(item);
            itemAdded(Size - 1);
        }


        inline void addAll(const List<Value>& list) {
            PointerList<Value>::addAll(list);
            for (size_t i = Size - list.Size; i < Size; i++)
                itemAdded(i);
        }

        inline void addAll(const std::initializer_list<Value>& list) {
            PointerList<Value>::addAll(list);
            for (size_t i = Size - list.size(); i < Size; i++)
                itemAdded(i);
        }

        inline void insert(size_t i, const Value& item) {
            PointerList<Value>::insert(i, item);
            itemAdded(i);
        }

        inline void set(size_t i, const Value& item) {
            PointerList<Value>::set(i, item);
            itemRemoved(i);
            itemAdded(i);
        }

        inline void removeAt(size_t i) {
            PointerList<Value>::removeAt(i);
            itemRemoved(i);
        }

        inline void remove(const Value& item) {
            PointerList<Value>::remove(item);
            if (item != nullptr)
                item->release();
        }

        inline void clear() {
            size_t s = List<Value>::size;
            PointerList<Value>::clear();
            for (size_t i = 0; i < s; i++)
                itemRemoved(s - i - 1);
        }
    };
}
