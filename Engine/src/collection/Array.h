#pragma once

#include "Collection.h"

namespace Ghurund {
    template<class Value> class Array:public Collection {
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

        inline size_t getSize()const {
            return size;
        }

        __declspec(property(get = getSize)) size_t Size;

        inline void set(size_t i, const Value &e) {
#ifdef _DEBUG
            if(i>=size)
                _ASSERT_EXPR(i>=size, _T("index out of bounds"));
#endif
            v[i] = e;
        }

        inline Value &get(size_t i)const {
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

        inline size_t indexOf(const Value &item) {
            for(size_t i = 0; i<size; i++)
                if(v[i]==item)
                    return i;
            return size;
        }

        inline bool contains(Value &item) {
            for(size_t i = 0; i<size; i++)
                if(v[i]==item)
                    return true;
            return false;
        }

        Value &operator[](size_t i) {
#ifdef _DEBUG
            if(i>=size)
                _ASSERT_EXPR(i>=size, _T("index out of bounds"));
#endif
            return v[i];
        }

        const Value &operator[](size_t i)const {
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

        inline void copyTo(Array<Value> &dest, size_t offset = 0) {
            for(size_t i = 0; i<size; i++)
                dest[i+offset] = v[i];
        }
    };

}