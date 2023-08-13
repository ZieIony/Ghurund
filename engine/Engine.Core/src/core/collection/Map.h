#pragma once

#include "CollectionWithCapacity.h"

#include <exception>
#include <map>

namespace Ghurund::Core {
    template<class Key, class Value>
    struct KeyValuePair {
        Key key;
        Value value;

        auto operator<=>(const KeyValuePair& other) const = default;
    };

    template<class Key, class Value> class Map:public CollectionWithCapacity {
    protected:
        typedef KeyValuePair<Key, Value> pair_t;

        pair_t* v;

    public:
        Map() {
            v = (pair_t*)ghnew uint8_t[sizeof(pair_t) * capacity];
        }

        Map(const Map& t1):CollectionWithCapacity(t1) {
            v = (pair_t*)ghnew uint8_t[sizeof(pair_t) * capacity];
            for (size_t i = 0; i < size; i++)
                new (v + i) pair_t(t1.v[i]);
        }

        Map(const std::initializer_list<pair_t>& list):CollectionWithCapacity(list.size()) {
            v = (pair_t*)ghnew uint8_t[sizeof(pair_t) * capacity];
            for (auto it = list.begin(); it != list.end(); it++) {
                new (v + size) pair_t(*it);
                size++;
            }
        }

        Map(Map&& t1) noexcept:CollectionWithCapacity(std::move(t1)) {
            v = t1.v;
            t1.v = nullptr;
        }

        virtual ~Map() {
            for (size_t i = 0; i < size; i++)
                v[i].~pair_t();
            delete[](uint8_t*)v;
        }

        inline size_t getSize()const {
            return size;
        }

        __declspec(property(get = getSize)) size_t Size;

        inline void resize(size_t c) {
            pair_t* v1 = (pair_t*)ghnew uint8_t[sizeof(pair_t) * c];
            _ASSERTE(sizeof(pair_t) * c != 0);
            capacity = c;
            if (c >= size) {
                for (size_t i = 0; i < size; i++) {
                    new (v1 + i) pair_t(v[i]);
                    v[i].~pair_t();
                }
            } else {
                for (size_t i = 0; i < c; i++) {
                    new (v1 + i) pair_t(v[i]);
                    v[i].~pair_t();
                }
                for (size_t i = c; i < size; i++)
                    v[i].~pair_t();
                size = c;
            }
            delete[](uint8_t*)v;
            v = v1;
        }

        inline void clear() {
            for (size_t i = 0; i < size; i++)
                v[i].~pair_t();
            __super::clear();
        }

        inline void set(const Key& key, const Value& value) {
            for (size_t i = 0; i < size; i++) {
                if (v[i].key == key) {
                    v[i].value = value;
                    return;
                }
            }
            if (size == capacity)
                resize(size + initial);
            new(v + size) pair_t(key, value);
            size++;
        }

        inline void setKey(size_t i, Key& key) {
            v[i].key = key;
        }

        inline void setValue(size_t i, Value& value) {
            v[i].value = value;
        }

        inline Key& getKey(size_t i) const {
            return v[i].key;
        }

        inline Value& getValue(size_t i) {
            return v[i].value;
        }

        inline const Value& getValue(size_t i) const {
            return v[i].value;
        }

        inline Value& get(const Key& key) {
            for (size_t i = 0; i < size; i++) {
                if (v[i].key == key)
                    return v[i].value;
            }
            throw std::exception("no value for given key");
        }

        inline const Value& get(const Key& key) const {
            for (size_t i = 0; i < size; i++) {
                if (v[i].key == key)
                    return v[i].value;
            }
            throw std::exception("no value for given key");
        }

        inline void remove(const Key& key) {
            for (size_t i = 0; i < size; i++) {
                if (v[i].key == key) {
                    size--;
                    v[i] = std::move(v[size]);
                    v[size].~pair_t();
                    return;
                }
            }
        }

        inline pair_t* begin() {
            return v;
        }

        inline pair_t* begin() const {
            return v;
        }

        inline pair_t* end() {
            return v + size;
        }

        inline pair_t* end() const {
            return v + size;
        }

        inline size_t indexOfKey(const Key& key) const {
            for (size_t i = 0; i < size; i++) {
                if (v[i].key == key)
                    return i;
            }
            return size;
        }

        inline size_t indexOfValue(const Value& value) const {
            for (size_t i = 0; i < size; i++) {
                if (v[i].value == value)
                    return i;
            }
            return size;
        }

        template<typename Predicate>
        inline size_t findKey(const Predicate& predicate) const {
            for (size_t i = 0; i < size; i++) {
                if (predicate(v[i].key))
                    return i;
            }
            return size;
        }

        template<typename Predicate>
        inline size_t findValue(const Predicate& predicate) const {
            for (size_t i = 0; i < size; i++) {
                if (predicate(v[i].key))
                    return i;
            }
            return size;
        }

        inline bool containsKey(const Key& item) const {
            for (size_t i = 0; i < size; i++)
                if (v[i].key == item)
                    return true;
            return false;
        }

        inline bool containsValue(const Value& item) const {
            for (size_t i = 0; i < size; i++)
                if (v[i].value == item)
                    return true;
            return false;
        }

        inline Value& operator[](const Key& key) {
            return get(key);
        }

        inline const Value& operator[](const Key& key) const {
            return get(key);
        }

        Map<Key, Value>& operator=(const Map<Key, Value>& other) {
            if (this == &other)
                return *this;
            for (size_t i = 0; i < size; i++)
                v[i].~pair_t();
            delete[](uint8_t*)v;
            __super::operator=(other);
            v = (pair_t*)ghnew uint8_t[sizeof(pair_t) * other.capacity];
            for (size_t i = 0; i < size; i++)
                new (v + i) pair_t(other.v[i]);
            return *this;
        }

        Map<Key, Value>& operator=(Map<Key, Value>&& other) noexcept {
            if (this == &other)
                return *this;
            for (size_t i = 0; i < size; i++)
                v[i].~pair_t();
            delete[](uint8_t*)v;
            __super::operator=(std::move(other));
            v = other.v;
            other.v = nullptr;
            return *this;
        }
    };
}