#pragma once

#include "CollectionWithCapacity.h"

#include <exception>

namespace Ghurund {

    template<class Key, class Value> class Map :public CollectionWithCapacity {
    protected:
        Key* k;
        Value* v;

    public:
        Map() {
            k = (Key*)ghnew char[sizeof(Key) * capacity];
            v = (Value*)ghnew char[sizeof(Value) * capacity];
        }

        Map(const Map& t1):CollectionWithCapacity(t1) {
            k = (Key*)ghnew char[sizeof(Key) * capacity];
            v = (Value*)ghnew char[sizeof(Value) * capacity];
            for (size_t i = 0; i < size; i++) {
                new (k + i) Key(t1.k[i]);
                new (v + i) Value(t1.v[i]);
            }
        }

        Map(Map&& t1) noexcept:CollectionWithCapacity(std::move(t1)) {
            k = t1.k;
            v = t1.v;
            t1.k = nullptr;
            t1.v = nullptr;
        }

        virtual ~Map() {
            for (size_t i = 0; i < size; i++) {
                k[i].~Key();
                v[i].~Value();
            }
            delete[] (char*)k;
            delete[] (char*)v;
        }

        inline size_t getSize()const {
            return size;
        }

        __declspec(property(get = getSize)) size_t Size;

        inline void resize(size_t c) {
            Key* k1 = (Key*)ghnew char[sizeof(Key) * c];
            Value* v1 = (Value*)ghnew char[sizeof(Value) * c];
            _ASSERTE(sizeof(Value) * c != 0);
            capacity = c;
            if (c >= size) {
                for (size_t i = 0; i < size; i++) {
                    new (k1 + i) Key(k[i]);
                    k[i].~Key();
                    new (v1 + i) Value(v[i]);
                    v[i].~Value();
                }
            } else {
                for (size_t i = 0; i < c; i++) {
                    new (k1 + i) Key(k[i]);
                    k[i].~Key();
                    new (v1 + i) Value(v[i]);
                    v[i].~Value();
                }
                for (size_t i = c; i < size; i++) {
                    k[i].~Key();
                    v[i].~Value();
                }
                size = c;
            }
            delete[](char*)k;
            delete[](char*)v;
            k = k1;
            v = v1;
        }

        inline void set(const Key& key, const Value& value) {
            for (size_t i = 0; i < size; i++) {
                if (k[i] == key) {
                    v[i] = value;
                    return;
                }
            }
            if (size == capacity)
                resize(size + initial);
            new(k + size) Key(key);
            new(v + size) Value(value);
            size++;
        }

        inline void setKey(size_t i, Key& key) {
            if (i >= capacity) {
                resize(i);
                new(k + i) Key(key);
            } else {
                k[i].~Key();
                new(k + i) Key(key);
            }
        }

        inline void setValue(size_t i, Value& value) {
            if (i >= capacity) {
                resize(i);
                new(v + i) Value(value);
            } else {
                v[i].~Value();
                new(v + i) Value(value);
            }
        }

        inline Key& getKey(size_t i) const {
            return k[i];
        }

        inline Value& getValue(size_t i) const {
            return v[i];
        }

        inline Value& get(const Key& key) const {
            for (size_t i = 0; i < size; i++) {
                if (k[i] == key)
                    return v[i];
            }
            throw std::exception("no value for given key");
        }

        inline void remove(const Key& key) {
            for (size_t i = 0; i < size; i++) {
                if (k[i] == key) {
                    k[i] = k[size - 1];
                    v[i] = v[size - 1];
                    size--;
                    return;
                }
            }
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

        inline size_t indexOfKey(const Key& key) const {
            for (size_t i = 0; i < size; i++) {
                if (k[i] == key)
                    return i;
            }
            return size;
        }

        inline size_t indexOfValue(const Value& value) const {
            for (size_t i = 0; i < size; i++) {
                if (v[i] == value)
                    return i;
            }
            return size;
        }

        inline bool containsKey(const Key& item) const {
            for (size_t i = 0; i < size; i++)
                if (k[i] == item)
                    return true;
            return false;
        }

        inline bool containsValue(const Value& item) const {
            for (size_t i = 0; i < size; i++)
                if (v[i] == item)
                    return true;
            return false;
        }

        inline const Value& operator[](const Key& key) const {
            return get(key);
        }

        Map<Key, Value>& operator=(const Map<Key, Value>& other) {
            if (this == &other)
                return *this;
            __super::operator=(other);
            delete[](char*)k;
            delete[](char*)v;
            k = (Key*)ghnew(char*)[sizeof(Key) * other.capacity];
            v = (Value*)ghnew(char*)[sizeof(Value) * other.capacity];
            for (size_t i = 0; i < size; i++) {
                new (k + i) Key(other.k[i]);
                new (v + i) Value(other.v[i]);
            }
            return *this;
        }

        Map<Key, Value>& operator=(const Map<Key, Value>&& other) {
            if (this == &other)
                return *this;
            __super::operator=(std::move(other));
            k = other.k;
            v = other.v;
            other.k = nullptr;
            other.v = nullptr;
            return *this;
        }
    };
}