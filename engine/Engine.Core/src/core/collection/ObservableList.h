#pragma once

#include "List.h"
#include "core/Event.h"

namespace Ghurund::Core {
    template<class Value>
    class ObservableList:public List<Value> {
    private:
        Event<ObservableList<Value>, Value&> onItemAdded = *this;
        Event<ObservableList<Value>, Value&> onItemRemoved = *this;

    public:
        inline Event<ObservableList<Value>, Value&>& getOnItemAdded() {
            return onItemAdded;
        }

        __declspec(property(get = getOnItemAdded)) Event<ObservableList<Value>, Value&>& OnItemAdded;

        inline Event<ObservableList<Value>, Value&>& getOnItemRemoved() {
            return onItemRemoved;
        }

        __declspec(property(get = getOnItemRemoved)) Event<ObservableList<Value>, Value&>& OnItemRemoved;

        inline void add(const Value& item) {
            List<Value>::add(item);
            onItemAdded(List<Value>::get(List<Value>::Size - 1));
        }

        inline void addAll(const List<Value>& list) {
            List<Value>::addAll(list);
            for (size_t i = List<Value>::Size - list.Size; i < List<Value>::Size; i++)
                onItemAdded(list[i]);
        }

        inline void addAll(const std::initializer_list<Value>& list) {
            List<Value>::addAll(list);
            for (size_t i = List<Value>::Size - list.size(); i < List<Value>::Size; i++)
                onItemAdded(list[i]);
        }

        inline void insert(size_t i, const Value& item) {
            List<Value>::insert(i, item);
            onItemAdded(item);
        }

        inline void set(size_t i, const Value& item) {
            List<Value>::set(i, item);
            onItemRemoved(item);
            onItemAdded(item);
        }

        inline void removeAt(size_t i) {
            Value& item = List<Value>::get(i);
            List<Value>::removeAt(i);
            onItemRemoved(item);
        }

        inline void remove(const Value& item) {
            List<Value>::remove(item);
            onItemRemoved(item);
        }

        inline void clear() {
            size_t s = List<Value>::Size;
            List<Value>::clear();
            for (size_t i = 0; i < s; i++)
                onItemRemoved(List<Value>::get(s - i - 1));
        }
    };
}
