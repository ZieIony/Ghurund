#pragma once

#include "Map.h"

namespace Ghurund {

    template<class Key, class Value>class HashMap:public Map<Key, Value> {
    private:
        int *h;
        std::function<int(const Key&)> hashFunc;

    public:
        HashMap(std::function<int(const Key&)> func) {
            h = ghnew int[capacity];
            hashFunc = func;
        }
        HashMap(const HashMap &t1) {
            /*
            capacity=t1.capacity;
            initial=t1.initial;
            size=t1.size;
            k=ghnew Key[capacity];
            memcpy(k,t1.k,sizeof(Key)*size);
            v=ghnew Value[capacity];
            memcpy(v,t1.v,sizeof(Value)*size);
            */
            h = ghnew int[capacity];
            memcpy(h, t1.h, sizeof(int)*size);
        }
        ~HashMap() {
            delete[]h;
        }

        inline void resize(size_t c) {
            Map::resize(c);
            int *h1 = ghnew int[c];
            memcpy(h1, h, sizeof(int)*std::min(size, c));
            delete[]h;
            h = h1;
        }

        inline void set(const Key &key, const Value &value) {
            int keyHash = hashFunc(key);
            for(size_t i = 0; i < size; i++) {
                if(h[i] == keyHash && k[i] == key) {
                    v[i] = value;
                    return;
                }
            }
            if(size == capacity)
                resize(size + initial);
            k[size] = key;
            v[size] = value;
            h[size] = hashFunc(key);
            size++;
        }
        inline void setKey(size_t i, const Key &key) {
            Map::setKey(i, key);
            h[i] = hashFunc(key);
        }
        inline Value &get(Key &key)const {
            int keyHash = hashFunc(key);
            for(size_t i = 0; i < size; i++) {
                if(h[i] == keyHash && k[i] == key)
                    return v[i];
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
        inline void remove(const Key &key) {
            int keyHash = hashFunc(key);
            for(size_t i = 0; i < size; i++) {
                if(h[i] == keyHash && k[i] == key) {
                    k[i] = k[size - 1];
                    v[i] = v[size - 1];
                    size--;
                    return;
                }
            }
        }
        inline size_t indexOf(const Key &key)const {
            int keyHash = hashFunc(key);
            for(size_t i = 0; i < size; i++)
                if(h[i] == keyHash && k[i] == key)
                    return i;
            return size;
        }
        inline bool contains(const Key &key) {
            int keyHash = hashFunc(key);
            for(size_t i = 0; i < size; i++)
                if(h[i] == keyHash && k[i] == key)
                    return true;
            return false;
        }
    };

}