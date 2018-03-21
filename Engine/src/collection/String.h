#pragma once

#include "Collection.h"
#include "core/Object.h"

namespace Ghurund {

    template <class Type> class GenericString {
    private:
        Type *v;
        int hash;
        size_t initial;
        size_t size;
        size_t capacity;

        inline void fit(size_t c) {
            if(capacity>=c)
                return;
            resize(capacity+initial>=c ? capacity+initial : c);
        }
        inline void resize(size_t c) {//if c<size some items will be lost, cannot resize to less than 1 item
            size_t c2 = std::max<size_t>(c, 1);
            Type *t1 = ghnew Type[c2];
            memcpy(t1, v, std::min(c, size)*sizeof(Type));
            capacity = c2;
            size = std::min(size, c);
            delete[] v;
            v = t1;
        }

    public:
        GenericString() {
            size = 1;   // with null terminator
            capacity = initial = Collection<size_t, Type>::INITIAL_CAPACITY;
            v = ghnew Type[capacity];
            v[size-1] = 0;
            hash = 0;
        }

        GenericString(const Type *str) {
            initial = Collection<size_t, Type>::INITIAL_CAPACITY;
            capacity = size = lengthOf(str)+1;
            v = ghnew Type[capacity];
            memcpy(v, str, size*sizeof(Type));
            computeHash();
        }

        GenericString(const Type *str, size_t length) {
            initial = Collection<size_t, Type>::INITIAL_CAPACITY;
            capacity = size = length+1;
            v = ghnew Type[capacity];
            memcpy(v, str, length*sizeof(Type));
            v[size-1] = 0;
            computeHash();
        }

        GenericString(const GenericString<Type> &string) {
            initial = Collection<size_t, Type>::INITIAL_CAPACITY;
            capacity = size = string.size;
            v = ghnew Type[capacity];
            memcpy(v, string.v, size*sizeof(Type));
            hash = string.hash;
        }

        ~GenericString() {
            delete[] v;
        }

        inline void add(Type e) {
            if(size+1>capacity)
                resize(capacity+initial);
            v[size-1] = e;
            size++;
            v[size-1] = 0;
        }
        inline void add(const Type *c) {
            size_t len = lengthOf(c)+1;
            fit(size+len);
            memcpy(v+size-1, c, (len+1)*sizeof(Type));
            size += len;
        }
        inline void add(const Type *c, size_t len) {
            fit(size+len);
            memcpy(v+size-1, c, len*sizeof(Type));
            size += len;
            v[size-1] = 0;
        }
        inline void set(size_t i, Type c) {
            v[i] = c;
        }
        inline Type get(size_t i)const {//possible segmentation fault
            return v[i];
        }
        inline const Type *getData()const {
            return v;
        }
        inline void setData(const Type *data) {
            size_t s = lengthOf(data)+1;
            delete[] v;
            v = ghnew Type[s];
            memcpy(this->v, data, s*sizeof(Type));
            capacity = size = s;
        }
        inline void setData(const Type *data, size_t len) {
            delete[] v;
            v = ghnew Type[len];
            memcpy(this->v, data, len*sizeof(Type));
            capacity = size = len;
        }

        inline size_t getLength()const {
            return size-1;
        }

        __declspec(property(get = getLength)) size_t Length;

        inline size_t getSize()const {
            return size;
        }

        __declspec(property(get = getSize)) size_t Size;

        Type &operator[](size_t i) {
            return v[i];
        }
        const Type &operator[](size_t i)const {
            return v[i];
        }

        GenericString &operator=(const GenericString &string) {
            size = string.size;
            initial = string.initial;
            capacity = string.capacity;
            delete[] v;
            v = new Type[capacity];
            memcpy(v, string.v, size*sizeof(Type));
            hash = string.hash;
            return *this;
        }

        void computeHash() {
            hash = hashCode(v, size-1);
        }

        bool operator==(const GenericString &string) const {
            return hash==string.hash&&size==string.size && size!=0&&memcmp(v, string.v, size*sizeof(Type))==0;
        }
    };

    typedef GenericString<wchar_t> UnicodeString;
    typedef GenericString<char> ASCIIString;

#ifdef UNICODE
    typedef UnicodeString String;
#else
    typedef ASCIIString String;
#endif

}