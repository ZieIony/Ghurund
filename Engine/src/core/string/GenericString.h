#pragma once

#include "Common.h"

#include "core/collection/Collection.h"

namespace Ghurund {

    template <class Type> class GenericString {
    protected:
        Type* v = nullptr;
        int hash;
        size_t initial;
        size_t size;
        size_t capacity;

        inline void fit(size_t c) {
            if (capacity >= c)
                return;
            resize(capacity + initial >= c ? capacity + initial : c);
        }
        inline void resize(size_t c) {//if c<size some items will be lost, cannot resize to less than 1 item
            size_t c2 = std::max<size_t>(c, 1);
            Type* t1 = ghnew Type[c2];
            memcpy(t1, v, std::min(c, size) * sizeof(Type));
            capacity = c2;
            size = std::min(size, c);
            delete[] v;
            v = t1;
        }

        void computeHash() {
            hash = hashCode(v, size - 1);
        }

    public:
        GenericString() {
            size = 1;   // with null terminator
            capacity = initial = Collection::INITIAL_CAPACITY;
            v = ghnew Type[capacity];
            v[size - 1] = 0;
            hash = 0;
        }

        GenericString(const Type* str) {
            initial = Collection::INITIAL_CAPACITY;
            capacity = size = lengthOf(str) + 1;
            v = ghnew Type[capacity];
            memcpy(v, str, size * sizeof(Type));
            computeHash();
        }

        GenericString(const Type* str, size_t length) {
            initial = Collection::INITIAL_CAPACITY;
            capacity = size = length + 1;
            v = ghnew Type[capacity];
            memcpy(v, str, length * sizeof(Type));
            v[size - 1] = 0;
            computeHash();
        }

        GenericString(const GenericString<Type>& string) {
            initial = Collection::INITIAL_CAPACITY;
            capacity = size = string.size;
            v = ghnew Type[capacity];
            memcpy(v, string.v, size * sizeof(Type));
            hash = string.hash;
        }

        GenericString(GenericString&& other) {
            v = other.v;
            size = other.size;
            initial = other.initial;
            capacity = other.capacity;

            other.v = nullptr;
            other.size = 0;
        }

        ~GenericString() {
            delete[] v;
        }

        inline void add(const Type e) {
            if (size + 1 > capacity)
                resize(capacity + initial);
            v[size - 1] = e;
            size++;
            v[size - 1] = 0;
            computeHash();
        }

        inline void add(const Type* str) {
            if (!str)
                return;
            size_t len = lengthOf(str);
            fit(size + len);
            memcpy(v + size - 1, str, len * sizeof(Type));
            size += len;
            v[size - 1] = 0;
            computeHash();
        }

        inline void add(const Type* str, size_t len) {
            if (!str)
                return;
            fit(size + len);
            memcpy(v + size - 1, str, len * sizeof(Type));
            size += len;
            v[size - 1] = 0;
            computeHash();
        }

        inline void set(size_t i, Type c) {
            v[i] = c;
            computeHash();
        }

        inline Type get(size_t i)const {
            return v[i];
        }

        inline void replace(Type from, Type to) {
            for (size_t i = 0; i < size; i++)
                if (v[i] == from)
                    v[i] = to;
        }

        inline void insert(size_t pos, Type str) {
            if (size + 1 > capacity)
                resize(capacity + initial);
            memcpy(v + pos + 1, v + pos, (size - pos) * sizeof(Type));
            v[pos] = str;
            size++;
            computeHash();
        }

        inline void insert(size_t pos, const Type* str) {
            if (!str)
                return;
            size_t len = lengthOf(str);
            fit(size + len);
            memcpy(v + pos + len, v + pos, (size - pos) * sizeof(Type));
            memcpy(v + pos, str, len * sizeof(Type));
            size += len;	// null terminator already present
            computeHash();
        }

        inline void insert(size_t pos, const Type* str, size_t len) {
            if (!str)
                return;
            fit(size + len);
            memcpy(v + pos + len, v + pos, (size - pos) * sizeof(Type));
            memcpy(v + pos, str, len * sizeof(Type));
            size += len;	// null terminator already present
            computeHash();
        }

        inline void remove(size_t pos, size_t length) {
            memcpy(v + pos, v + pos + length, (size - pos - length) * sizeof(Type));
            size -= length;
            computeHash();
        }

        inline void clear() {
            delete[] v;
            size = capacity = initial;
            v = ghnew Type[capacity];
            computeHash();
        }

        inline const Type* getData()const {
            return v;
        }
        inline void setData(const Type* data) {
            size_t len = lengthOf(data) + 1;
            delete[] v;
            v = ghnew Type[len];
            memcpy(this->v, data, len * sizeof(Type));
            capacity = size = len;
            computeHash();
        }
        inline void setData(const Type* data, size_t len) {
            delete[] v;
            v = ghnew Type[len];
            memcpy(this->v, data, len * sizeof(Type));
            capacity = size = len;
            computeHash();
        }

        inline size_t getLength()const {
            return size - 1;
        }

        __declspec(property(get = getLength)) size_t Length;

        inline size_t getSize()const {
            return size;
        }

        __declspec(property(get = getSize)) size_t Size;

        Type& operator[](size_t i) {
            return v[i];
        }
        const Type& operator[](size_t i)const {
            return v[i];
        }

        bool operator==(const GenericString& string) const {
            return hash == string.hash && size == string.size && size != 0 && memcmp(v, string.v, Length * sizeof(Type)) == 0;
        }

        bool operator==(const GenericString& string) {
            return hash == string.hash && size == string.size && size != 0 && memcmp(v, string.v, Length * sizeof(Type)) == 0;
        }

        bool operator==(const Type* str) const {
            return memcmp(v, str, Length * sizeof(Type)) == 0;
        }

        bool operator==(const Type* str) {
            return memcmp(v, str, Length * sizeof(Type)) == 0;
        }

        GenericString& operator=(GenericString&& other) noexcept {
            if (this == &other)
                return *this;

            delete[] v;

            v = other.v;
            size = other.size;
            initial = other.initial;
            capacity = other.capacity;

            other.v = nullptr;
            other.size = 0;

            return *this;
        }

        operator const Type* ()const {
            return v;
        }

        size_t find(const Type* str, size_t start = 0) const {
            size_t strSize = lengthOf(str);
            for (size_t i = start; i <= size - strSize; i++) {
                if (memcmp(&v[i], str, strSize * sizeof(Type)) == 0)
                    return i;
            }
            return size;
        }

        size_t findLast(const Type* str) const {
            size_t strSize = lengthOf(str);
            for (size_t i = size - strSize; i > 0; i--) {
                if (memcmp(&v[i], str, strSize * sizeof(Type)) == 0)
                    return i;
            }

            if (memcmp(v, str, strSize * sizeof(Type)) == 0)
                return 0;
            return size;
        }

        bool startsWith(const Type* str) const {
            size_t i = 0;
            while (true) {
                if (str[i] == (Type)'\0')
                    return true;
                if (str[i] != v[i])
                    return false;
                i++;
            }
        }

        bool endsWith(const Type* str) const {
            size_t l = lengthOf(str);
            if (l > Length)
                return false;
            size_t i = 0;
            while (true) {
                if (str[i] == (Type)'\0')
                    return true;
                if (str[i] != v[Length - l + i])
                    return false;
                i++;
            }
        }

        bool isEmpty()const {
            return size == 1;
        }

        __declspec(property(get = isEmpty)) bool Empty;

        int getHash()const {
            return hash;
        }

        __declspec(property(get = getHash)) int Hash;
    };
}