#pragma once

#include "Map.h"
#include "core/Hashing.h"

namespace Ghurund::Core {

    template<class Key, class Value>
    class HashMap:public Map<Key, Value> {
    private:
        typedef Map<Key, Value> M;

        int* h;

    public:
        HashMap() {
            h = ghnew int[M::capacity];
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
            h = ghnew int[M::capacity];
            memcpy(h, t1.h, sizeof(int) * M::size);
        }

        ~HashMap() {
            delete[] h;
        }

        inline void resize(size_t c) {
            Map::resize(c);
            int* h1 = ghnew int[c];
            memcpy(h1, h, sizeof(int) * std::min(M::size, c));
            delete[]h;
            h = h1;
        }

        inline void set(const Key& key, const Value& value) {
            int keyHash = hashCode(key);
            for (size_t i = 0; i < M::size; i++) {
                if (h[i] == keyHash && M::k[i] == key) {
                    M::v[i] = value;
                    return;
                }
            }
            if (M::size == M::capacity)
                resize(M::size + M::initial);
            M::k[M::size] = key;
            M::v[M::size] = value;
            M::h[M::size] = hashCode(key);
            M::size++;
        }

        inline void setKey(size_t i, const Key& key) {
            M::setKey(i, key);
            h[i] = hashCode(key);
        }

        inline Value& get(Key& key)const {
            int keyHash = hashCode(key);
            for (size_t i = 0; i < M::size; i++) {
                if (h[i] == keyHash && M::k[i] == key)
                    return M::v[i];
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
            int keyHash = hashCode(key);
            for (size_t i = 0; i < M::size; i++) {
                if (h[i] == keyHash && M::k[i] == key) {
                    M::k[i] = M::k[M::size - 1];
                    M::v[i] = M::v[M::size - 1];
                    M::size--;
                    return;
                }
            }
        }

        inline size_t indexOf(const Key& key)const {
            int keyHash = hashCode(key);
            for (size_t i = 0; i < M::size; i++)
                if (h[i] == keyHash && M::k[i] == key)
                    return i;
            return M::size;
        }

        inline bool contains(const Key& key) {
            int keyHash = hashCode(key);
            for (size_t i = 0; i < M::size; i++)
                if (h[i] == keyHash && M::k[i] == key)
                    return true;
            return false;
        }
    };

}