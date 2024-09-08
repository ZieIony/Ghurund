#pragma once

#include "List.h"
#include "core/Event.h"

namespace Ghurund::Core {
    template<class Value>
    class ObservableList:public List<Value> {
    public:
        Event<ObservableList<Value>, Value&> itemAdded = *this;
        Event<ObservableList<Value>, Value&> itemRemoved = *this;

        inline void add(const Value& item) {
            List<Value>::add(item);
            itemAdded(List<Value>::get(List<Value>::Size - 1));
        }

        inline void addAll(const List<Value>& list) {
            List<Value>::addAll(list);
            for (size_t i = List<Value>::Size - list.Size; i < List<Value>::Size; i++)
                itemAdded(list[i]);
        }

        inline void addAll(const std::initializer_list<Value>& list) {
            List<Value>::addAll(list);
            for (size_t i = List<Value>::Size - list.size(); i < List<Value>::Size; i++)
                itemAdded(list[i]);
        }

        inline void insert(size_t i, const Value& item) {
            List<Value>::insert(i, item);
            itemAdded(item);
        }

        inline void set(size_t i, const Value& item) {
            List<Value>::set(i, item);
            itemRemoved(item);
            itemAdded(item);
        }

        inline void removeAt(size_t i) {
            Value& item = List<Value>::get(i);
            List<Value>::removeAt(i);
            itemRemoved(item);
        }

        inline void remove(const Value& item) {
            List<Value>::remove(item);
            itemRemoved(item);
        }

        inline void clear() {
            size_t s = List<Value>::Size;
            List<Value>::clear();
            for (size_t i = 0; i < s; i++)
                itemRemoved(List<Value>::get(s - i - 1));
        }
    };
}
