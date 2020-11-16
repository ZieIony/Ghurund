#pragma once

#include "Map.h"

namespace Ghurund {

    template<class Key, class Value> class PointerMap:public Map<Key, Value> {
    public:
        PointerMap() {}

        virtual ~PointerMap() {
            for (size_t i = 0; i < Map<Key, Value>::size; i++)
                if (Map<Key, Value>::v[i] != nullptr)
                    Map<Key, Value>::v[i]->release();
        }

        inline void set(const Key& key, const Value& value) {
            for (size_t i = 0; i < Map<Key, Value>::size; i++) {
                if (Map<Key, Value>::k[i] == key) {
                    if (Map<Key, Value>::v[i] != nullptr)
                        Map<Key, Value>::v[i]->release();
                    Map<Key, Value>::v[i] = value;
                    if (value != nullptr)
                        value->addReference();
                    return;
                }
            }
            if (Map<Key, Value>::size == Map<Key, Value>::capacity)
                Map<Key, Value>::resize(Map<Key, Value>::size + Map<Key, Value>::initial);
            new(Map<Key, Value>::k + Map<Key, Value>::size) Key(key);
            new(Map<Key, Value>::v + Map<Key, Value>::size) Value(value);
            if (value != nullptr)
                value->addReference();
            Map<Key, Value>::size++;
        }

        inline void setValue(size_t i, Value& value) {
            if (i >= Map<Key, Value>::capacity)
                Map<Key, Value>::resize(i);
            if (Map<Key, Value>::v[i] != nullptr)
                Map<Key, Value>::v[i]->release();
            Map<Key, Value>::v[i] = value;
            if (value != nullptr)
                value->addReference();
        }

        inline void remove(const Key& key) {
            for (size_t i = 0; i < Map<Key, Value>::size; i++) {
                if (Map<Key, Value>::k[i] == key) {
                    Map<Key, Value>::k[i] = Map<Key, Value>::k[Map<Key, Value>::size - 1];
                    if (Map<Key, Value>::v[i] != nullptr)
                        Map<Key, Value>::v[i]->release();
                    Map<Key, Value>::v[i] = Map<Key, Value>::v[Map<Key, Value>::size - 1];
                    Map<Key, Value>::size--;
                    return;
                }
            }
        }

        inline void clear() {
            for (size_t i = 0; i < Map<Key, Value>::size; i++)
                if (Map<Key, Value>::v[i] != nullptr)
                    Map<Key, Value>::v[i]->release();
            Map<Key, Value>::size = 0;
        }
    };
}