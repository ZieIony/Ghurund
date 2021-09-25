#pragma once

#include "Map.h"

namespace Ghurund::Core {

    template<class Key, class Value>
    class HashMap:public Map<Key, Value> {
    private:
        int* h;
        std::function<int(const Key&)> hashFunc;

    public:
        HashMap(std::function<int(const Key&)> func) {
            h = ghnew int[Map<Key, Value>::capacity];
            hashFunc = func;
        }
        HashMap(const HashMap& t1) {
            /*
            capacity=t1.capacity;
            initial=t1.initial;
            size=t1.size;
            k=ghnew Key[capacity];
            memcpy(k,t1.k,sizeof(Key)*size);
            v=ghnew Value[capacity];
            memcpy(v,t1.v,sizeof(Value)*size);
            */
            h = ghnew int[Map<Key, Value>::capacity];
            memcpy(h, t1.h, sizeof(int) * Map<Key, Value>::size);
        }
        ~HashMap() {
            delete[] h;
        }

        inline void resize(size_t c) {
            Map::resize(c);
            int* h1 = ghnew int[c];
            memcpy(h1, h, sizeof(int) * std::min(Map<Key, Value>::size, c));
            delete[]h;
            h = h1;
        }

        inline void set(const Key& key, const Value& value) {
            int keyHash = hashFunc(key);
            for (size_t i = 0; i < Map<Key, Value>::size; i++) {
                if (h[i] == keyHash && Map<Key, Value>::k[i] == key) {
                    Map<Key, Value>::v[i] = value;
                    return;
                }
            }
            if (Map<Key, Value>::size == Map<Key, Value>::capacity)
                resize(Map<Key, Value>::size + Map<Key, Value>::initial);
            Map<Key, Value>::k[Map<Key, Value>::size] = key;
            Map<Key, Value>::v[Map<Key, Value>::size] = value;
            Map<Key, Value>::h[Map<Key, Value>::size] = hashFunc(key);
            Map<Key, Value>::size++;
        }
        inline void setKey(size_t i, const Key& key) {
            Map<Key, Value>::setKey(i, key);
            h[i] = hashFunc(key);
        }
        inline Value& get(Key& key)const {
            int keyHash = hashFunc(key);
            for (size_t i = 0; i < Map<Key, Value>::size; i++) {
                if (h[i] == keyHash && Map<Key, Value>::k[i] == key)
                    return Map<Key, Value>::v[i];
            }
            return Value();
        }
        /*
        inline void remove(size_t i){//je?li size==0, to program si? wywali
        k[i]=k[size-1];
        v[i]=v[size-1];
        size--;
        }
        */
        inline void remove(const Key& key) {
            int keyHash = hashFunc(key);
            for (size_t i = 0; i < Map<Key, Value>::size; i++) {
                if (h[i] == keyHash && Map<Key, Value>::k[i] == key) {
                    Map<Key, Value>::k[i] = Map<Key, Value>::k[Map<Key, Value>::size - 1];
                    Map<Key, Value>::v[i] = Map<Key, Value>::v[Map<Key, Value>::size - 1];
                    Map<Key, Value>::size--;
                    return;
                }
            }
        }
        inline size_t indexOf(const Key& key)const {
            int keyHash = hashFunc(key);
            for (size_t i = 0; i < Map<Key, Value>::size; i++)
                if (h[i] == keyHash && Map<Key, Value>::k[i] == key)
                    return i;
            return Map<Key, Value>::size;
        }
        inline bool contains(const Key& key) {
            int keyHash = hashFunc(key);
            for (size_t i = 0; i < Map<Key, Value>::size; i++)
                if (h[i] == keyHash && Map<Key, Value>::k[i] == key)
                    return true;
            return false;
        }
    };

}