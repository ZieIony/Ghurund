#pragma once

#include "GenericString.h"

namespace Ghurund {

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

        inline void add(const char e);

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
            wchar_t *prevV = v;
            wchar_t *stringV = string.v;
            v = new wchar_t[capacity];
            memcpy(v, stringV, size*sizeof(wchar_t));
            hash = string.hash;
            delete[] prevV;
            return *this;
        }

        UnicodeString operator+(const wchar_t *str) {
            UnicodeString copy(*this);
            copy.add(str);
            return copy;
        }

        UnicodeString operator+(const wchar_t str) {
            UnicodeString copy(*this);
            copy.add(str);
            return copy;
        }

        UnicodeString operator+(const UnicodeString &string) const {
            UnicodeString copy(*this);
            copy.add(string.getData());
            return copy;
        }

        UnicodeString operator+(const char *str) {
            UnicodeString copy(*this);
            copy.add(str);
            return copy;
        }

        UnicodeString operator+(const char str) {
            UnicodeString copy(*this);
            copy.add(str);
            return copy;
        }

        UnicodeString operator+(const GenericString<char> &string) const {
            UnicodeString copy(*this);
            copy.add(string.getData());
            return copy;
        }

        UnicodeString subString(size_t start)const {
            return UnicodeString(v+start);
        }

        UnicodeString subString(size_t start, size_t length)const {
            return UnicodeString(v+start, length);
        }

        List<UnicodeString> split(const wchar_t* d)const;

        UnicodeString toLowerCase() {
            UnicodeString copy(*this);
            for(size_t i = 0; i < Length; i++)
                copy.v[i] = (wchar_t)towlower(copy.v[i]);
            return copy;
        }

        UnicodeString toUpperCase() {
            UnicodeString copy(*this);
            for(size_t i = 0; i < Length; i++)
                copy.v[i] = (wchar_t)towupper(copy.v[i]);
            return copy;
        }

        UnicodeString trim() {
            size_t i, j, l = Length;
            for(i = 0; i < l && iswspace(v[i]); i++);
            for(j = l - 1; j > i && iswspace(v[j]); j--);
            return UnicodeString(v + i, j - i + 1);
        }
    };

#ifdef UNICODE
    typedef UnicodeString String;
#endif

}