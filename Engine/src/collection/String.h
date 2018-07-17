#pragma once

#include "List.h"

namespace Ghurund {

    template <class Type> class GenericString {
    protected:
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
            computeHash();
        }
        inline void add(const Type *c) {
            size_t len = lengthOf(c)+1;
            fit(size+len);
            memcpy(v+size-1, c, len*sizeof(Type));
            size += len-1;	// null terminator already present
            computeHash();
        }
        inline void add(const Type *c, size_t len) {
            fit(size+len);
            memcpy(v+size-1, c, len*sizeof(Type));
            size += len;
            v[size-1] = 0;
            computeHash();
        }
        inline void set(size_t i, Type c) {
            v[i] = c;
            computeHash();
        }
        inline Type get(size_t i)const {
            return v[i];
        }
        inline const Type *getData()const {
            return v;
        }
        inline void setData(const Type *data) {
            size_t len = lengthOf(data)+1;
            delete[] v;
            v = ghnew Type[len];
            memcpy(this->v, data, len*sizeof(Type));
            capacity = size = len;
            computeHash();
        }
        inline void setData(const Type *data, size_t len) {
            delete[] v;
            v = ghnew Type[len];
            memcpy(this->v, data, len*sizeof(Type));
            capacity = size = len;
            computeHash();
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

        void computeHash() {
            hash = hashCode(v, size-1);
        }

        bool operator==(const GenericString &string) const {
            return hash==string.hash&&size==string.size && size!=0&&memcmp(v, string.v, Length*sizeof(Type))==0;
        }

        bool operator==(const GenericString &string) {
            return hash==string.hash&&size==string.size && size!=0&&memcmp(v, string.v, Length*sizeof(Type))==0;
        }

        bool operator==(const Type *str) const {
            return memcmp(v, str, Length*sizeof(Type))==0;
        }

        operator const Type *()const {
            return v;
        }

        size_t find(const GenericString<Type> &str, size_t start = 0)const {
            for(size_t i = start; i<=size-str.Size; i++) {
                for(size_t j = 0; j<str.Length; j++) {
                    if(v[i+j]!=str[j])
                        goto strNotFound;
                }
                return i;
            strNotFound:;
            }
            return size;
        }

        bool startsWith(const Type *str)const {
            size_t i = 0;
            while(true) {
                if(str[i]=='\0')
                    return true;
                if(str[i]!=v[i])
                    return false;
                i++;
            }
        }

        bool endsWith(const Type *str)const {
            size_t l = lengthOf(str);
            if(l>Length)
                return false;
            size_t i = Length-l;
            while(true) {
                if(str[i]=='\0')
                    return true;
                if(str[i]!=v[i])
                    return false;
                i++;
            }
        }

        bool isEmpty()const {
            return size==1;
        }

        __declspec(property(get = isEmpty)) bool Empty;

    };



    class UnicodeString: public GenericString<wchar_t> {
    public:
        using GenericString<wchar_t>::GenericString;

        UnicodeString() {}

        UnicodeString(const char *str) {
            add(str);
        }

        UnicodeString(const char *str, size_t length) {
            add(str, length);
        }

        UnicodeString(const GenericString<char> &string) {
            add(string.getData());
        }

        using GenericString<wchar_t>::add;

        inline void add(const char *str) {
            wchar_t *wstr = toWideChar(str);
            add(wstr);
            delete[] wstr;
        }

        inline void add(const char *str, size_t len) {
            wchar_t *wstr = toWideChar(str);
            add(wstr, len);
            delete[] wstr;
        }

        using GenericString<wchar_t>::operator==;
    
        bool operator==(const char *str) const {
            wchar_t *wstr = toWideChar(str);
            bool result = memcmp(v, wstr, Length*sizeof(wchar_t))==0;
            delete[] wstr;
            return result;
        }

        UnicodeString &operator=(const UnicodeString &string) {
            size = string.size;
            initial = string.initial;
            capacity = string.capacity;
            delete[] v;
            v = new wchar_t[capacity];
            memcpy(v, string.v, size*sizeof(wchar_t));
            hash = string.hash;
            return *this;
        }

        UnicodeString operator+(const wchar_t *str) {
            UnicodeString copy(*this);
            copy.add(str);
            return copy;
        }

        UnicodeString operator+(const UnicodeString &string) {
            return *this + string.getData();
        }

        UnicodeString operator+(const char *str) {
            UnicodeString copy(*this);
            copy.add(str);
            return copy;
        }

        UnicodeString operator+(const GenericString<char> &string) {
            return *this + string.getData();
        }

        UnicodeString subString(size_t start)const {
            return UnicodeString(v+start);
        }

        UnicodeString subString(size_t start, size_t length)const {
            return UnicodeString(v+start, length);
        }

        List<UnicodeString> split(const UnicodeString &d)const {
            List<UnicodeString> list;
            size_t index = 0;
            while(index<Length) {
                size_t nextIndex = find(d, index);
                if(nextIndex==index) {
                } else if(nextIndex==size) {
                    UnicodeString str = subString(index, size-index-1);
                    list.add(str);
                    break;
                } else {
                    UnicodeString str = subString(index, nextIndex-index);
                    list.add(str);
                }
                index = nextIndex+d.Length;
            }
            return list;
        }

        using GenericString<wchar_t>::startsWith;

        bool startsWith(const char *str)const {
            size_t i = 0;
            while(true) {
                if(str[i]=='\0')
                    return true;
                if(str[i]!=v[i])
                    return false;
                i++;
            }
        }

        using GenericString<wchar_t>::endsWith;

        bool endsWith(const char *str)const {
            size_t l = lengthOf(str);
            if(l>Length)
                return false;
            size_t i = 0;
            while(true) {
                if(str[i]=='\0')
                    return true;
                if(str[i]!=v[Length-l+i])
                    return false;
                i++;
            }
        }

        UnicodeString toLowerCase() {
            UnicodeString copy(*this);
            for(size_t i = 0; i < Length; i++)
                copy.v[i] = (wchar_t)towlower(copy.v[i]);
            return copy;
        }

		UnicodeString toUpperCase() {
			UnicodeString copy(*this);
			for (size_t i = 0; i < Length; i++)
				copy.v[i] = (wchar_t)towupper(copy.v[i]);
			return copy;
		}

		UnicodeString trim() {
			size_t i, j, l = Length;
			for (i = 0; i < l && iswspace(v[i]); i++);
			for (j = l - 1; j > i && iswspace(v[j]); j--);
			return UnicodeString(v + i, j - i + 1);
		}
	};



    class ASCIIString: public GenericString<char> {
    public:
        using GenericString<char>::GenericString;

        ASCIIString() {}

        ASCIIString(const wchar_t *str) {
            add(str);
        }

        ASCIIString(const wchar_t *str, size_t length) {
            add(str, length);
        }

        ASCIIString(const GenericString<wchar_t> &string) {
            add(string.getData());
        }

        using GenericString<char>::add;

        inline void add(const wchar_t *str) {
            char *cstr = toMultiByte(str);
            add(cstr);
            delete[] cstr;
        }

        inline void add(const wchar_t *str, size_t len) {
            char *cstr = toMultiByte(str);
            add(cstr, len);
            delete[] cstr;
        }

        using GenericString<char>::operator==;
   
        bool operator==(const wchar_t *str) const {
            char *cstr = toMultiByte(str);
            bool result = memcmp(v, cstr, Length*sizeof(char))==0;
            delete[] cstr;
            return result;
        }

        ASCIIString &operator=(const ASCIIString &string) {
            size = string.size;
            initial = string.initial;
            capacity = string.capacity;
            delete[] v;
            v = new char[capacity];
            memcpy(v, string.v, size*sizeof(char));
            hash = string.hash;
            return *this;
        }

        ASCIIString operator+(const char *str) {
            UnicodeString copy(*this);
            copy.add(str);
            return copy;
        }

        ASCIIString operator+(const ASCIIString &string) {
            return *this + string.getData();
        }


        ASCIIString operator+(const wchar_t *str) {
            ASCIIString copy(*this);
            copy.add(str);
            return copy;
        }

        ASCIIString operator+(const GenericString<wchar_t> &string) {
            return *this + string.getData();
        }

        ASCIIString subString(size_t start)const {
            return ASCIIString(v+start);
        }

        ASCIIString subString(size_t start, size_t length)const {
            return ASCIIString(v+start, length);
        }

        List<ASCIIString> split(const ASCIIString &d)const {
            List<ASCIIString> list;
            size_t index = 0;
            while(index<Length) {
                size_t nextIndex = find(d, index);
                if(nextIndex==index) {
                } else if(nextIndex==size) {
                    ASCIIString str = subString(index, size-index-1);
                    list.add(str);
                    break;
                } else {
                    ASCIIString str = subString(index, nextIndex-index);
                    list.add(str);
                }
                index = nextIndex+d.Length;
            }
            return list;
        }

        using GenericString<char>::startsWith;

        bool startsWith(const wchar_t *str)const {
            size_t i = 0;
            while(true) {
                if(str[i]=='\0')
                    return true;
                if(str[i]!=v[i])
                    return false;
                i++;
            }
        }

        using GenericString<char>::endsWith;

        bool endsWith(const wchar_t *str)const {
            size_t l = lengthOf(str);
            if(l>Length)
                return false;
            size_t i = 0;
            while(true) {
                if(str[i]=='\0')
                    return true;
                if(str[i]!=v[Length-l+i])
                    return false;
                i++;
            }
        }

        ASCIIString toLowerCase() {
            ASCIIString copy(*this);
            for(size_t i = 0; i < Length; i++)
                copy.v[i] = (char)tolower(copy.v[i]);
            return copy;
        }

        ASCIIString toUpperCase() {
            ASCIIString copy(*this);
            for(size_t i = 0; i < Length; i++)
                copy.v[i] = (char)toupper(copy.v[i]);
            return copy;
        }

		ASCIIString trim() {
			size_t i, j, l = Length;
			for (i = 0; i < l && isspace(v[i]); i++);
			for (j = l - 1; j > i && isspace(v[j]); j--);
			return ASCIIString(v + i, j - i + 1);
		}
	};

#ifdef UNICODE
    typedef UnicodeString String;
#else
    typedef ASCIIString String;
#endif

}