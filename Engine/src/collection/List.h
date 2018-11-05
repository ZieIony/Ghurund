#pragma once

#include "Collection.h"
#include <functional>

namespace Ghurund {
    template<class Value> class List:public Collection {
    protected:
        Value *v;

#ifdef GHURUND_EDITOR
        std::function<void()> onItemAdded, onItemRemoved, onItemChanged;
#endif

        static const std::function<int(const void*, const void*)> DEFAULT_COMPARISON_FUNCTION;

    public:
        List() {
            v = ghnew Value[capacity];
        }

        List(size_t initial) {
            this->initial = capacity = initial;
            v = ghnew Value[capacity];
        }

        List(const List &t1) {
            capacity = t1.capacity;
            initial = t1.initial;
            size = t1.size;
            v = ghnew Value[capacity];
            for(size_t i = 0; i<size; i++)
                v[i] = t1.v[i];
        }

        List(std::initializer_list<Value> list) {
            size = initial = capacity = list.size();
            v = ghnew Value[capacity];
            int i = 0;
            for(auto it = list.begin(); it != list.end(); ++it)
                v[i++] = *it;
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

        inline size_t getSize()const {
            return size;
        }

        __declspec(property(get = getSize)) size_t Size;

        inline size_t getCapacity()const {
            return capacity;
        }

        inline void resize(size_t c) {//if c<size some items will be lost, cannot resize to less than 1 item
            size_t c2 = std::max<size_t>(c, 1);
            Value *t1 = ghnew Value[c2];
            capacity = c2;
            size = std::min(size, c);
            for(size_t i = 0; i<size; i++)
                t1[i] = v[i];
            delete[] v;
            v = t1;
        }

        inline void add(const Value &e) {//allows to add null item
            if(size==capacity)
                resize(capacity+initial);
            v[size] = e;
            size++;
#ifdef GHURUND_EDITOR
            if(onItemAdded!=nullptr)
                onItemAdded();
#endif
        }

        inline void insert(size_t i, const Value &item) {
#ifdef _DEBUG
            if(i>=size)
                _ASSERT_EXPR(i>=size, _T("index out of bounds"));
#endif
            if(size==capacity)
                resize(capacity+initial);
            v[size] = v[i];
            v[i] = item;
            size++;
        }

        inline void insertKeepOrder(size_t i, const Value &item) {
            if(size==capacity)
                resize(capacity+initial);
            if(i!=size-1)
                memmove(&v[i+1], &v[i], size-1-i);
            v[i] = item;
            size++;
        }

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

        inline void removeAt(size_t i) {
#ifdef _DEBUG
            if(i>=size)
                _ASSERT_EXPR(i>=size, _T("index out of bounds"));
#endif
            v[i] = v[size-1];
            size--;
        }

        inline void removeAtKeepOrder(size_t i) {
#ifdef _DEBUG
            if(i>=size)
                _ASSERT_EXPR(i>=size, _T("index out of bounds"));
#endif
            if(i!=size-1)
                memmove(&v[i], &v[i+1], size-1-i);
            size--;
        }

        inline void remove(const Value &item) {
            size_t i = indexOf(item);
#ifdef _DEBUG
            if(i>=size)
                _ASSERT_EXPR(i>=size, _T("index out of bounds"));
#endif
            v[i] = v[size-1];
            size--;
        }

        inline void removeKeepOrder(const Value &item) {
            size_t i = indexOf(item);
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

        inline size_t indexOf(const Value &item) {
            for(size_t i = 0; i<size; i++)
                if(v[i]==item)
                    return i;
            return size;
        }

        inline bool contains(const Value &item) {
            for(size_t i = 0; i<size; i++)
                if(v[i]==item)
                    return true;
            return false;
        }

        inline Value &operator[](size_t i) {
#ifdef _DEBUG
            if(i>=size)
                _ASSERT_EXPR(i>=size, _T("index out of bounds"));
#endif
            return v[i];
        }

        inline const Value &operator[](size_t i)const {
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

        inline void sort(std::function<int(const void*, const void*)> comparisonFunction = DEFAULT_COMPARISON_FUNCTION) {
            qsort(v, size, sizeof(Type), comparisonFunction);
        }
    };

}