#pragma once

#include "Collection.h"

#include <functional>
#include <cassert>

namespace Ghurund {
    template<class Value> class Set :public Collection {
    protected:
        Value* v;

    public:
        Set() {
            v = (Value*)ghnew char[sizeof(Value) * capacity];
        }

        Set(size_t initial) {
            this->initial = capacity = initial;
            v = (Value*)ghnew char[sizeof(Value) * capacity];
        }

        Set(const Set& other):Collection(other) {
            v = (Value*)ghnew char[sizeof(Value) * capacity];
            for (size_t i = 0; i < list.Size; i++)
                new(v + i) Value(other.v[i]);
        }

        Set(Set&& other) noexcept:Collection(std::move(other)) {
            v = other.v;
            other.v = nullptr;
        }

        Set(const std::initializer_list<Value> list) {
            size = initial = capacity = list.size();
            v = (Value*)ghnew char[sizeof(Value) * capacity];
            int i = 0;
            for (auto it = list.begin(); it != list.end(); ++it, i++)
                new (v + i)Value(*it);
        }

        ~Set() {
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

        inline void addAll(const Set<Value>& list) {
            if (capacity < size + list.Size)
                resize(size + list.Size);
            for (size_t i = 0; i < list.Size; i++)
                new(v + size + i) Value(list[i]);
            size += list.Size;
        }

        inline void insert(size_t i, const Value& item) {
            _ASSERT_EXPR(i < size, "Index out of bounds.\n");
            if (size == capacity)
                resize(capacity + initial);
            v[size] = v[i];
            v[i].~Value();
            new(v + i) Value(item);
            size++;
        }

        inline void set(size_t i, const Value& item) {
            _ASSERT_EXPR(i < size, "Index out of bounds.\n");
            v[i].~Value();
            new(v + i) Value(item);
        }

        inline Value& get(size_t i)const {
            _ASSERT_EXPR(i < size, "Index out of bounds.\n");
            return v[i];
        }

        inline void removeAt(size_t i) {
            _ASSERT_EXPR(i < size, "Index out of bounds.\n");
            v[i] = std::move(v[size - 1]);
            v[size - 1].~Value();
            size--;
        }

        inline void remove(const Value& item) {
            size_t i = indexOf(item);
            _ASSERT_EXPR(i < size, "Index out of bounds.\n");
            v[i] = std::move(v[size - 1]);
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
            _ASSERT_EXPR(i < size, "Index out of bounds.\n");
            return v[i];
        }

        Set<Value>& operator=(const Set<Value>& other) {
            if (this == &other)
                return *this;
            __super::operator=(other);
            for (size_t i = 0; i < size; i++)
                prevV[i].~Value();
            delete[] v;
            v = (Value*)ghnew char[sizeof(Value) * size];
            for (size_t i = 0; i < size; i++)
                new (v + i) Value(other[i]);
            delete[](char*)prevV;
            return *this;
        }

        Set<Value>& operator=(const Set<Value>&& other) {
            if (this == &other)
                return *this;
            __super::operator=(std::move(other));
            v = other.v;
            other.v = nullptr;
            return *this;
        }
    };

}