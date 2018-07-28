#pragma once

#include "Collection.h"

namespace Ghurund {
    template<class Value, class Key = size_t> class Array:public Collection<Key, Value> {
    protected:
        Value *v;

    public:
        Array(size_t size) {
            this->size = size;
            v = ghnew Value[size];
        }

        Array(const Array &t1) {
            size = t1.size;
            v = ghnew Value[size];
            for(size_t i = 0; i<size; i++)
                v[i] = t1.v[i];
        }

        Array(const std::initializer_list<Value> list) {
            size = list.size();
            v = ghnew Value[size];
            int i = 0;
            for(auto it = list.begin(); it != list.end(); ++it)
                v[i++] = *it;
        }

        ~Array() {
            delete[] v;
        }

        inline Key getSize()const {
            return size;
        }

        __declspec(property(get = getSize)) Key Size;

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

        inline Value *begin() {
            return v;
        }

        inline Value *end() {
            return v+size;
        }

        inline Key indexOf(const Value &item) {
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
        }
    };

}