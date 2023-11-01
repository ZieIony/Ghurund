#pragma once

#include "core/TypeSequence.h"
#include "Map.h"

namespace Ghurund::Core {
    template<typename Owner, typename Value>
    class TypeMap {
    private:
        template<typename T>
        class CollectionSequence:public TypeSequence<Owner, size_t, T> {};

        Map<size_t, Value> items;

    public:
        inline size_t getSize()const {
            return items.getSize();
        }

        __declspec(property(get = getSize)) size_t Size;

        template<typename T>
        inline void set(const Value& t) {
            size_t id = CollectionSequence<T>::value();
            if (id >= items.Size)
                items.resize(id + 1);
            items.set(id, t);
        }

        template<typename T>
        inline Value& get() {
            size_t id = CollectionSequence<T>::value();
            return items.get(id);
        }

        template<typename T>
        inline const Value& get() const {
            size_t id = CollectionSequence<T>::value();
            return items.get(id);
        }

        template<typename T>
        inline void remove() {
            size_t id = CollectionSequence<T>::value();
            items.remove(id);
        }

        inline KeyValuePair<size_t, Value>* begin() {
            return items.begin();
        }

        inline KeyValuePair<size_t, Value>* begin() const {
            return items.begin();
        }

        inline KeyValuePair<size_t, Value>* end() {
            return items.end();
        }

        inline KeyValuePair<size_t, Value>* end() const {
            return items.end();
        }

        template<typename T>
        inline bool contains() const {
            size_t id = CollectionSequence<T>::value();
            return items.contains(id);
        }

        inline bool containsValue(const Value& item) const {
            return items.containsValue(item);
        }

        inline void clear() {
            items.clear();
        }
    };
}