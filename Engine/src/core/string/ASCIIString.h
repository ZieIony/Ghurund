#pragma once

#include "GenericString.h"
#include "core/collection/Array.h"

namespace Ghurund {

    class ASCIIString: public GenericString<char> {
    public:
        using GenericString<char>::GenericString;

        ASCIIString() {}

        ASCIIString(const ASCIIString& string):GenericString<char>(string) {}

        ASCIIString(ASCIIString&& string):GenericString<char>(std::move(string)) {}

        ASCIIString(const wchar_t* str) {
            add(str);
        }

        ASCIIString(const wchar_t* str, size_t length) {
            add(str, length);
        }

        ASCIIString(const GenericString<wchar_t>& string) {
            add(string.getData());
        }

        using GenericString<char>::add;

        void add(const wchar_t e);

        inline void add(const wchar_t* str) {
            if (!str)
                return;
            char* cstr = toMultiByte(str);
            add(cstr);
            delete[] cstr;
        }

        inline void add(const wchar_t* str, size_t len) {
            if (!str)
                return;
            char* cstr = toMultiByte(str);
            add(cstr, len);
            delete[] cstr;
        }

        using GenericString<char>::operator==;

        bool operator==(const wchar_t* str) const {
            if (!str)
                return false;
            char* cstr = toMultiByte(str);
            bool result = memcmp(v, cstr, Length * sizeof(char)) == 0;
            delete[] cstr;
            return result;
        }

        using GenericString<char>::operator=;

        ASCIIString& operator=(const ASCIIString& string) {
            size = string.size;
            initial = string.initial;
            capacity = string.capacity;
            char* prevV = v;
            char* stringV = string.v;
            v = new char[capacity];
            memcpy(v, stringV, size * sizeof(char));
            hash = string.hash;
            delete[] prevV;
            return *this;
        }

        template<typename Type>
        ASCIIString operator+(const Type str) {
            ASCIIString copy(*this);
            copy.add(str);
            return copy;
        }

        ASCIIString subString(size_t start)const {
            return ASCIIString(v + start);
        }

        ASCIIString subString(size_t start, size_t length)const {
            return ASCIIString(v + start, length);
        }

        Array<ASCIIString> split(const char* d)const;

        ASCIIString toLowerCase() {
            ASCIIString copy(*this);
            for (size_t i = 0; i < Length; i++)
                copy.v[i] = (char)tolower(copy.v[i]);
            return copy;
        }

        ASCIIString toUpperCase() {
            ASCIIString copy(*this);
            for (size_t i = 0; i < Length; i++)
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

}