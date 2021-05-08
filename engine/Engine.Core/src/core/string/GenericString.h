#pragma once

#include "core/string/TextUtils.h"

#include <algorithm>
#undef min
#undef max

namespace Ghurund {

    template <class T> class GenericString {
    private:
        const static size_t INITIAL_CAPACITY = 10;

    protected:
        T* v = nullptr;
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
            T* t1 = ghnew T[c2];
            memcpy(t1, v, std::min(c, size) * sizeof(T));
            capacity = c2;
            size = std::min(size, c);
            delete[] v;
            v = t1;
        }

        inline void computeHash() {
            hash = hashCode(v, size - 1);
        }

    public:
        GenericString() {
            size = 1;   // with null terminator
            capacity = initial = INITIAL_CAPACITY;
            v = ghnew T[capacity];
            v[size - 1] = 0;
            hash = 0;
        }

        GenericString(const T* str) {
            initial = INITIAL_CAPACITY;
            capacity = size = lengthOf(str) + 1;
            v = ghnew T[capacity];
            memcpy(v, str, size * sizeof(T));
            computeHash();
        }

        GenericString(const T* str, size_t length) {
            initial = INITIAL_CAPACITY;
            capacity = size = length + 1;
            v = ghnew T[capacity];
            memcpy(v, str, length * sizeof(T));
            v[size - 1] = 0;
            computeHash();
        }

        GenericString(const GenericString<T>& string) {
            initial = INITIAL_CAPACITY;
            capacity = size = string.size;
            v = ghnew T[capacity];
            memcpy(v, string.v, size * sizeof(T));
            hash = string.hash;
        }

        GenericString(GenericString&& other) noexcept {
            v = other.v;
            size = other.size;
            initial = other.initial;
            capacity = other.capacity;
            hash = other.hash;

            other.v = nullptr;
            other.size = 0;
        }

        ~GenericString() {
            delete[] v;
        }

        inline T* begin() {
            return v;
        }

        inline T* begin() const {
            return v;
        }

        inline T* end() {
            return v + size;
        }

        inline T* end() const {
            return v + size;
        }

        inline void add(const T e) {
            if (size + 1 > capacity)
                resize(capacity + initial);
            v[size - 1] = e;
            size++;
            v[size - 1] = 0;
            computeHash();
        }

        inline void add(const T* str) {
            if (!str)
                return;
            size_t len = lengthOf(str);
            fit(size + len);
            memcpy(v + size - 1, str, len * sizeof(T));
            size += len;
            v[size - 1] = 0;
            computeHash();
        }

        inline void add(const T* str, size_t len) {
            if (!str)
                return;
            fit(size + len);
            memcpy(v + size - 1, str, len * sizeof(T));
            size += len;
            v[size - 1] = 0;
            computeHash();
        }

        inline void set(size_t i, T c) {
            v[i] = c;
            computeHash();
        }

        inline T get(size_t i)const {
            return v[i];
        }

        inline void replace(T from, T to) {
            bool updated = false;
            for (size_t i = 0; i < size; i++) {
                if (v[i] == from) {
                    v[i] = to;
                    updated = true;
                }
            }
            if (updated)
                computeHash();
        }

        inline void replace(const T* from, const T* to) {
            bool updated = false;
            size_t fromLength = lengthOf(from);
            size_t toLength = lengthOf(to);
            size_t next = 0;
            while (true) {
                next = find(from, next);
                if (next >= size)
                    break;
                if (toLength != fromLength) {
                    fit(size + toLength - fromLength);
                    memcpy(v + next + toLength, v + next + fromLength, (size - next - fromLength) * sizeof(T));
                    size += toLength - fromLength;
                }
                memcpy(v + next, to, toLength * sizeof(T));
                next += toLength;
                updated = true;
            }
            if (updated)
                computeHash();
        }

        inline void insert(size_t pos, T str) {
            if (size + 1 > capacity)
                resize(capacity + initial);
            memcpy(v + pos + 1, v + pos, (size - pos) * sizeof(T));
            v[pos] = str;
            size++;
            computeHash();
        }

        inline void insert(size_t pos, const T* str) {
            if (!str)
                return;
            size_t len = lengthOf(str);
            fit(size + len);
            memcpy(v + pos + len, v + pos, (size - pos) * sizeof(T));
            memcpy(v + pos, str, len * sizeof(T));
            size += len;	// null terminator already present
            computeHash();
        }

        inline void insert(size_t pos, const T* str, size_t len) {
            if (!str)
                return;
            fit(size + len);
            memcpy(v + pos + len, v + pos, (size - pos) * sizeof(T));
            memcpy(v + pos, str, len * sizeof(T));
            size += len;	// null terminator already present
            computeHash();
        }

        inline void remove(size_t pos, size_t length) {
            memcpy(v + pos, v + pos + length, (size - pos - length) * sizeof(T));
            size -= length;
            computeHash();
        }

        inline void clear() {
            delete[] v;
            size = capacity = initial;
            v = ghnew T[capacity];
            computeHash();
        }

        inline const T* getData() const {
            return v;
        }

        inline void setData(const T* data) {
            size_t len = lengthOf(data) + 1;
            delete[] v;
            v = ghnew T[len];
            memcpy(this->v, data, len * sizeof(T));
            capacity = size = len;
            computeHash();
        }

        __declspec(property(get = getData, put = setData)) const T* Data;

        inline void setData(const T* data, size_t len) {
            delete[] v;
            v = ghnew T[len];
            memcpy(this->v, data, len * sizeof(T));
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

        inline T& operator[](size_t i) {
            return v[i];
        }

        inline const T& operator[](size_t i) const {
            return v[i];
        }

        bool operator==(const GenericString& string) const {
            return hash == string.hash && size == string.size && size != 0 && memcmp(v, string.v, Length * sizeof(T)) == 0;
        }

        bool operator==(const T* str) const {
            return lengthOf(str) == Length && memcmp(v, str, Length * sizeof(T)) == 0;
        }

        GenericString& operator=(const GenericString<T>& string) {
            size = string.size;
            initial = string.initial;
            capacity = string.capacity;
            T* prevV = v;
            T* stringV = string.v;
            v = new T[capacity];
            memcpy(v, stringV, size * sizeof(T));
            hash = string.hash;
            delete[] prevV;
            return *this;
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

        size_t find(const T* str, size_t start = 0) const {
            size_t strSize = lengthOf(str);
            for (size_t i = start; i <= size - strSize; i++) {
                if (memcmp(&v[i], str, strSize * sizeof(T)) == 0)
                    return i;
            }
            return size;
        }

        size_t findLast(const T* str) const {
            size_t strSize = lengthOf(str);
            for (size_t i = size - strSize; i > 0; i--) {
                if (memcmp(&v[i], str, strSize * sizeof(T)) == 0)
                    return i;
            }

            if (memcmp(v, str, strSize * sizeof(T)) == 0)
                return 0;
            return size;
        }

        bool startsWith(const T* str) const {
            size_t i = 0;
            while (true) {
                if (str[i] == (T)'\0')
                    return true;
                if (str[i] != v[i])
                    return false;
                i++;
            }
        }

        bool endsWith(const T* str) const {
            size_t l = lengthOf(str);
            if (l > Length)
                return false;
            size_t i = 0;
            while (true) {
                if (str[i] == (T)'\0')
                    return true;
                if (str[i] != v[Length - l + i])
                    return false;
                i++;
            }
        }

        inline bool isEmpty() const {
            return size == 1;
        }

        __declspec(property(get = isEmpty)) bool Empty;

        inline int getHash() const {
            return hash;
        }

        __declspec(property(get = getHash)) int Hash;
    };
}