#pragma once

#include "Map.h"

namespace Ghurund {

    template<class Key, class Value> class PointerMap:public Map<Key, Value> {
    public:
        PointerMap() {}

        virtual ~PointerMap() {
            for(size_t i = 0; i<size; i++)
                if(v[i]!=nullptr)
                    v[i]->release();
        }

        inline void set(const Key &key, const Value &value) {
            for(size_t i = 0; i < size; i++) {
                if(k[i] == key) {
                    if(v[i]!=nullptr)
                        v[i]->release();
                    v[i] = value;
                    if(value!=nullptr)
                        value->addReference();
                    return;
                }
            }
            if(size == capacity)
                resize(size + initial);
            k[size] = key;
            v[size] = value;
            if(value!=nullptr)
                value->addReference();
            size++;
        }

        inline void setValue(size_t i, Value &value) {
            if(i >= capacity)
                resize(i);
            if(v[i]!=nullptr)
                v[i]->release();
            v[i] = value;
            if(value!=nullptr)
                value->addReference();
        }

        inline void remove(const Key &key) {
            for(size_t i = 0; i < size; i++) {
                if(k[i] == key) {
                    k[i] = k[size - 1];
                    if(v[i]!=nullptr)
                        v[i]->release();
                    v[i] = v[size - 1];
                    size--;
                    return;
                }
            }
        }

        inline void clear() {
            for(size_t i = 0; i<size; i++)
                if(v[i]!=nullptr)
                    v[i]->release();
            size = 0;
        }
    };
}