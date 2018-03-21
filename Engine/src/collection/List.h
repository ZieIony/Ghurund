#pragma once

#include "Collection.h"

namespace Ghurund {
    template<class Value, class Key = size_t>class List:public Collection<Key, Value> {
    protected:
        Value *v;

    public:
        List() {
            v = ghnew Value[capacity];
        }

        List(size_t initial) {
            this->initial = this->capacity = initial;
            v = ghnew Value[capacity];
        }

        List(const List &t1) {
            capacity = t1.capacity;
            initial = t1.initial;
            size = t1.size;
            v = ghnew Value[capacity];
            memcpy(v, t1.v, sizeof(Value)*size);
        }

        ~List() {
            delete[] v;
        }

        /*		Set *clone(){
        Set<Value> *table=ghnew Set<Value>(capacity);
        table->size=size;
        memcpy(table->v,v,sizeof(Value)*size);
        return table;
        }*/

        inline Key getSize()const {
            return size;
        }

        __declspec(property(get = getSize)) Key Size;

        inline Key getCapacity()const {
            return capacity;
        }

        inline void resize(Key c) {//if c<size some items will be lost, cannot resize to less than 1 item
            Key c2 = std::max<Key>(c, 1);
            Value *t1 = ghnew Value[c2];
            memcpy(t1, v, std::min(c, size)*sizeof(Value));
            //memset(t1+min(c,size),0,(c2-min(c,size))*sizeof(Value));
            capacity = c2;
            size = std::min(size, c);
            delete[]v;
            v = t1;
        }

        inline void add(const Value &e) {//allows to add null item
            if(size==capacity)
                resize(capacity+initial);
            v[size] = e;
            size++;
            return;
        }

        inline void set(Key i, const Value &e) {
#ifdef _DEBUG
            if(i>=size)
                _ASSERT_EXPR(i>=size, _T("index out of bounds"));
#endif
            v[i] = e;
        }

        inline Value &get(Key i)const {
#ifdef _DEBUG
            if(i>=size)
                _ASSERT_EXPR(i>=size, _T("index out of bounds"));
#endif
            return v[i];
        }

        inline void remove(Key i) {
#ifdef _DEBUG
            if(i>=size)
                _ASSERT_EXPR(i>=size, _T("index out of bounds"));
#endif
            //			if(size>1)	// as fast and dangerous as possible :P
            v[i] = v[size-1];
            size--;
        }

        inline void removeKeepOrder(Key i) {
#ifdef _DEBUG
            if(i>=size)
                _ASSERT_EXPR(i>=size, _T("index out of bounds"));
#endif
            if(i!=size-1)
                memmove(&v[i], &v[i+1], size-1-i);
            size--;
        }

        inline void remove(const Value &item) {
            Key i = find(item);
#ifdef _DEBUG
            if(i>=size)
                _ASSERT_EXPR(i>=size, _T("index out of bounds"));
#endif
            v[i] = v[size-1];
            size--;
        }

        inline void removeKeepOrder(const Value &item) {
            Key i = find(item);
#ifdef _DEBUG
            if(i>=size)
                _ASSERT_EXPR(i>=size, _T("index out of bounds"));
#endif
            if(i!=size-1)
                memmove(&v[i], &v[i+1], size-1-i);
            size--;
        }

        inline Value *begin() {
            return v;
        }

        inline Value *end() {
            return v+size;
        }

        inline Key find(const Value &item) {
            for(Key i = 0; i<size; i++)
                if(v[i]==item)
                    return i;
            return size;
        }

        inline bool contains(Value &item) {
            for(Key i = 0; i<size; i++)
                if(v[i]==item)
                    return true;
            return false;
        }

        Value &operator[](Key i) {
#ifdef _DEBUG
            if(i>=size)
                _ASSERT_EXPR(i>=size, _T("index out of bounds"));
#endif
            return v[i];
        }

        const Value &operator[](Key i)const {
#ifdef _DEBUG
            if(i>=size)
                _ASSERT_EXPR(i>=size, _T("index out of bounds"));
#endif
            return v[i];
        }

        inline void deleteItems() {
            for(size_t i = 0; i<size; i++)
                delete v[i];
            size = 0;
        }
    };

}