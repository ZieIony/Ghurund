#pragma once

#include "Collection.h"
#include "List.h"

namespace Ghurund::Core {
    template<class Value> class Array:public Collection {
    protected:
        Value* v;

    public:
        Array(size_t size) {
            this->size = size;
            v = (Value*)ghnew char[sizeof(Value) * size];
            for (size_t i = 0; i < size; i++)
                new (v + i) Value();
        }

        Array(const Value* data, size_t size, size_t offset = 0) {
            this->size = size;
            v = (Value*)ghnew char[sizeof(Value) * size];
            memcpy(v, data + offset, size * sizeof(Value));
        }

        Array(const Array& t1):Collection(t1) {
            v = (Value*)ghnew char[sizeof(Value) * size];
            for (size_t i = 0; i < size; i++)
                new (v + i) Value(t1[i]);
        }

        Array(Array&& t1) noexcept:Collection(std::move(t1)) {
            v = t1.v;
            t1.v = nullptr;
        }

        Array(const std::initializer_list<Value> list) {
            size = list.size();
            v = (Value*)ghnew char[sizeof(Value) * size];
            int i = 0;
            for (auto it = list.begin(); it != list.end(); ++it, i++)
                new(v + i)Value(*it);
        }

        Array(const List<Value>& list) {
            size = list.Size;
            v = (Value*)ghnew char[sizeof(Value) * size];
            int i = 0;
            for (auto it = list.begin(); it != list.end(); ++it, i++)
                new(v + i)Value(*it);
        }

        ~Array() {
            for (size_t i = 0; i < size; i++)
                v[i].~Value();
            delete[](char*)v;
        }

        inline void set(size_t i, const Value& e) {
            v[i].~Value();
            new(v + i) Value(e);
        }

        inline Value& get(size_t i) const {
            return v[i];
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

        inline bool contains(Value& item) const {
            for (size_t i = 0; i < size; i++)
                if (v[i] == item)
                    return true;
            return false;
        }

        Value& operator[](size_t i) {
            return v[i];
        }

        const Value& operator[](size_t i) const {
            return v[i];
        }

        Array<Value>& operator=(const Array<Value>& other) {
            if (this == &other)
                return *this;
            size = other.size;
            for (size_t i = 0; i < size; i++)
                v[i].~Value();
            delete[](char*)v;
            v = (Value*)ghnew char[sizeof(Value) * size];
            for (size_t i = 0; i < size; i++)
                new (v + i) Value(other[i]);
            return *this;
        }

        Array<Value>& operator=(Array<Value>&& other) {
            if (this == &other)
                return *this;
            size = other.size;
            other.size = 0;
            v = other.v;
            other.v = nullptr;
            return *this;
        }

        Array<Value>& operator=(const std::initializer_list<Value>& other) {
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

        inline void deleteItems() {
            for (size_t i = 0; i < size; i++) {
                delete v[i];
                v[i].~Value();
            }
        }

        inline void copyTo(Array<Value>& dest, size_t offset = 0) const {
            for (size_t i = 0; i < size; i++)
                dest.set(i + offset, v[i]);
        }
    };

}