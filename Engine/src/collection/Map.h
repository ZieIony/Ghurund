#pragma once

#include "Ghurund.h"
#include "Collection.h"
#include <functional>

namespace Ghurund {

    template<class Key, class Value>class Map:public Collection<Key, Value> {//klasa nie dla idiot?w
    protected:
        Key *k;
        Value *v;

    public:
        Map() {
            k = ghnew Key[capacity];
            v = ghnew Value[capacity];
            //memset(k,0,sizeof(Key)*capacity);
            //memset(v,0,sizeof(Value)*capacity);
        }
        Map(const Map &t1) {
            capacity = t1.capacity;
            initial = t1.initial;
            size = t1.size;
            k = ghnew Key[capacity];
            memcpy(k, t1.k, sizeof(Key)*size);
            v = ghnew Value[capacity];
            memcpy(v, t1.v, sizeof(Value)*size);
        }
        virtual ~Map() {
            delete[]k;
            delete[]v;
        }

        inline size_t getSize()const {
            return size;
        }

        __declspec(property(get = getSize)) size_t Size;

        inline void resize(size_t c) {
            capacity = c;
            Key *k1 = ghnew Key[c];
            memcpy(k1, k, sizeof(Key)*std::min(size, c));
            delete[]k;
            k = k1;
            Value *v1 = ghnew Value[c];
            memcpy(v1, v, sizeof(Value)*std::min(size, c));
            delete[]v;
            v = v1;
        }

        inline void set(const Key &key, const Value &value) {
            for(size_t i = 0; i<size; i++) {
                if(k[i]==key) {
                    v[i] = value;
                    return;
                }
            }
            if(size==capacity)
                resize(size+initial);
            k[size] = key;
            v[size] = value;
            size++;
        }
        inline void setKey(size_t i, Key &key) {
            if(i>=capacity)
                resize(i);
            k[i] = key;
        }
        inline void setValue(size_t i, Value &value) {
            if(i>=capacity)
                resize(i);
            v[i] = value;
        }
        inline Key getKey(size_t i) const {
            return k[i];
        }
        inline Value getValue(size_t i) const {
            return v[i];
        }
        inline Value get(const Key &key) const {
            for(size_t i = 0; i<size; i++) {
                if(k[i]==key)
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
            for(size_t i = 0; i<size; i++) {
                if(k[i]==key) {
                    k[i] = k[size-1];
                    v[i] = v[size-1];
                    size--;
                    return;
                }
            }
        }
        inline void clear(size_t vvalue = 0, size_t kvalue = 0) {
            size = 0;
        }
        inline Value *begin() {
            return v;
        }
        inline Value *end() {
            return v+size;
        }
        inline size_t find(const Key &item)const {
            for(size_t i = 0; i<size; i++)
                if(k[i]==item)
                    return i;
            return size;
        }
        inline bool contains(const Key &item) {
            for(size_t i = 0; i<size; i++)
                if(k[i]==item)
                    return true;
            return false;
        }
    };

    template<class Key, class Value>class HashMap:public Map<Key, Value> {
    private:
        int *h;
        std::function<int(Key&)> hashFunc;

    public:
        HashMap() {
            h = ghnew int[capacity];
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
        void setHashFunc(std::function<int(Key&)> func) {
            hashFunc = func;
        }
        inline void resize(size_t c) {
            Map::resize(c);
            int *h1 = ghnew int[c];
            memcpy(h1, h, sizeof(int)*min(size, c));
            delete[]h;
            h = h1;
        }
        inline void set(Key key, Value value) {
            int keyHash = hashFunc(&key);
            for(size_t i = 0; i<size; i++) {
                if(h[i]==keyHash && k[i]==key) {
                    v[i] = value;
                    return;
                }
            }
            if(size==capacity)
                resize(size+initial);
            k[size] = key;
            v[size] = value;
            h[size] = hashFunc->execute(&key);
            size++;
        }
        inline void setKey(size_t i, Key key) {
            Map::setKey(i, key);
            h[i] = hashFunc->execute(&key);
        }
        inline Value get(Key key)const {
            int keyHash = hashFunc->execute(&key);
            for(size_t i = 0; i<size; i++) {
                if(h[i]==keyHash && k[i]==key)
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
        inline void remove(Key key) {
            int keyHash = hashFunc->execute(&key);
            for(size_t i = 0; i<size; i++) {
                if(h[i]==keyHash && k[i]==key) {
                    k[i] = k[size-1];
                    v[i] = v[size-1];
                    size--;
                    return;
                }
            }
        }
        inline size_t find(Key key)const {
            int keyHash = hashFunc->execute(&key);
            for(size_t i = 0; i<size; i++)
                if(h[i]==keyHash && k[i]==key)
                    return i;
            return size;
        }
        inline bool contains(Key key) {
            int keyHash = hashFunc->execute(&key);
            for(size_t i = 0; i<size; i++)
                if(h[i]==keyHash && k[i]==key)
                    return true;
            return false;
        }
    };

}