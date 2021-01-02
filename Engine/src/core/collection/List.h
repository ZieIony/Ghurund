#pragma once

#include "Collection.h"

namespace Ghurund {
    template<class Value> class List:public Collection {
    protected:
        Value* v;

    public:
        List() {
            v = (Value*)ghnew char[sizeof(Value) * capacity];
        }

        List(size_t initial) {
            this->initial = capacity = initial;
            v = (Value*)ghnew char[sizeof(Value) * capacity];
        }

        List(const List& t1):Collection(t1) {
            v = (Value*)ghnew char[sizeof(Value) * capacity];
            for (size_t i = 0; i < size; i++)
                new (v + i)Value(t1[i]);
        }

        List(List&& t1) noexcept:Collection(std::move(t1)) {
            v = t1.v;
            t1.v = nullptr;
        }

        List(const std::initializer_list<Value> list) {
            size = initial = capacity = list.size();
            v = (Value*)ghnew char[sizeof(Value) * capacity];
            int i = 0;
            for (auto it = list.begin(); it != list.end(); ++it, i++)
                new (v + i)Value(*it);
        }

        ~List() {
            for (size_t i = 0; i < size; i++)
                v[i].~Value();
            delete[](char*)v;
        }

        inline size_t getSize()const {
            return size;
        }

        __declspec(property(get = getSize)) size_t Size;

        inline size_t getCapacity()const {
            return capacity;
        }

        inline void resize(size_t c) {
            Value* other = (Value*)ghnew char[sizeof(Value) * c];
            capacity = c;
            if (c >= size) {
                for (size_t i = 0; i < size; i++) {
                    new (other + i) Value(v[i]);
                    v[i].~Value();
                }
            } else {
                for (size_t i = 0; i < c; i++) {
                    new (other + i) Value(v[i]);
                    v[i].~Value();
                }
                for (size_t i = c; i < size; i++)
                    v[i].~Value();
                size = c;
            }
            delete[](char*)v;
            v = other;
        }

        inline void add(const Value& item) {
            if (size == capacity)
                resize((size_t)(capacity * 1.6));
            new(v + size) Value(item);
            size++;
        }

        inline void addAll(const List<Value>& list) {
            if (capacity < size + list.Size)
                resize(size + list.Size);
            for (size_t i = 0; i < list.Size; i++)
                new(v + size + i) Value(list[i]);
            size += list.Size;
        }

        inline void addAll(const std::initializer_list<Value>& list) {
            if (capacity < size + list.size())
                resize(size + list.size());
            const Value* l = list.begin();
            for (size_t i = 0; i < list.size(); i++, l++)
                new(v + size + i) Value(*l);
            size += list.size();
        }

        inline void insert(size_t i, const Value& item) {
            if (size == capacity)
                resize((size_t)(capacity * 1.6));
            if (i < size) {
                v[size] = v[size - 1];
                for (size_t j = size - 1; j > i; j--)
                    v[j] = std::move(v[j - 1]);
            }
            v[i].~Value();
            new(v + i) Value(item);
            size++;
        }

        inline void set(size_t i, const Value& item) {
            v[i].~Value();
            new(v + i) Value(item);
        }

        inline Value& get(size_t i)const {
            return v[i];
        }

        inline void removeAt(size_t i) {
            if (i != size - 1) {
                for (size_t j = i; j < size - 1; j++)
                    v[j] = std::move(v[j + 1]);
            }
            v[size - 1].~Value();
            size--;
        }

        inline void remove(const Value& item) {
            size_t i = indexOf(item);
            if (i != size - 1) {
                for (size_t j = i; j < size - 1; j++)
                    v[j] = std::move(v[j + 1]);
            }
            v[size - 1].~Value();
            size--;
        }

        inline Value* begin() {
            return v;
        }

        inline Value* begin() const {
            return v;
        }

        inline Value* end() {
            return v + size;
        }

        inline Value* end() const {
            return v + size;
        }

        inline size_t indexOf(const Value& item) const {
            for (size_t i = 0; i < size; i++)
                if (v[i] == item)
                    return i;
            return size;
        }

        inline bool contains(const Value& item) const {
            for (size_t i = 0; i < size; i++)
                if (v[i] == item)
                    return true;
            return false;
        }

        inline Value& operator[](size_t i)const {
            return v[i];
        }

        List<Value>& operator=(const List<Value>& other) {
            if (this == &other)
                return *this;
            __super::operator=(other);
            for (size_t i = 0; i < size; i++)
                v[i].~Value();
            delete[](char*)v;
            v = (Value*)ghnew char[sizeof(Value) * size];
            for (size_t i = 0; i < size; i++)
                new (v + i) Value(other[i]);
            return *this;
        }

        List<Value>& operator=(const std::initializer_list<Value>& other) {
            size = other.size();
            for (size_t i = 0; i < size; i++)
                v[i].~Value();
            delete[](char*)v;
            v = (Value*)ghnew char[sizeof(Value) * size];
            const Value* l = other.begin();
            for (size_t i = 0; i < size; i++, l++)
                new (v + i) Value(*l);
            return *this;
        }

        List<Value>& operator=(const List<Value>&& other) {
            if (this == &other)
                return *this;
            __super::operator=(std::move(other));
            v = other.v;
            other.v = nullptr;
            return *this;
        }

        inline void deleteItems() {
            for (size_t i = 0; i < size; i++) {
                delete v[i];
                v[i].~Value();
            }
            size = 0;
        }
    };

}