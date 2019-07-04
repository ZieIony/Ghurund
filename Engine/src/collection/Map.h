#pragma once

#include "Collection.h"
#include <functional>

namespace Ghurund {

    template<class Key, class Value> class Map:public Collection {
    protected:
        Key* k;
        Value* v;

    public:
        Map() {
            k = ghnew Key[capacity];
            v = ghnew Value[capacity];
        }

        Map(const Map& t1) {
            capacity = t1.capacity;
            initial = t1.initial;
            size = t1.size;
            k = ghnew Key[capacity];
            v = ghnew Value[capacity];
            for (size_t i = 0; i < size; i++) {
                k[i] = t1.k[i];
                v[i] = t1.v[i];
            }
        }

        virtual ~Map() {
            delete[] k;
            delete[] v;
        }

        inline size_t getSize()const {
            return size;
        }

        __declspec(property(get = getSize)) size_t Size;

        inline void resize(size_t c) {
            capacity = c;
            size = std::min(size, c);

            Key* k1 = ghnew Key[c];
            Value* v1 = ghnew Value[c];
            for (size_t i = 0; i < size; i++) {
                k1[i] = k[i];
                v1[i] = v[i];
            }
            delete[] k;
            k = k1;
            delete[] v;
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
            k[size] = key;
            v[size] = value;
            size++;
        }

        inline void setKey(size_t i, Key& key) {
            if (i >= capacity)
                resize(i);
            k[i] = key;
        }

        inline void setValue(size_t i, Value& value) {
            if (i >= capacity)
                resize(i);
            v[i] = value;
        }

        inline Key& getKey(size_t i) const {
            return k[i];
        }

        inline Value& getValue(size_t i) const {
            return v[i];
        }

        inline size_t findKey(const Key& key) const {
            for (size_t i = 0; i < size; i++) {
                if (k[i] == key)
                    return i;
            }
            return size;
        }

        inline size_t findValue(const Value& value) const {
            for (size_t i = 0; i < size; i++) {
                if (v[i] == value)
                    return i;
            }
            return size;
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

        inline Value* end() {
            return v + size;
        }

        inline size_t indexOf(const Key& item)const {
            for (size_t i = 0; i < size; i++)
                if (k[i] == item)
                    return i;
            return size;
        }

        inline bool contains(const Key& item) const {
            for (size_t i = 0; i < size; i++)
                if (k[i] == item)
                    return true;
            return false;
        }

        inline Value& operator[](Key& key) {
            return get(key);
        }

        inline const Value& operator[](const Key& key)const {
            return get(key);
        }
    };
}