#pragma once

#include "GenericString.h"
#include "core/collection/Array.h"

namespace Ghurund {

    class AString: public GenericString<char> {
    public:
        using GenericString<char>::GenericString;

        AString() {}

        AString(const AString& string):GenericString<char>(string) {}

        AString(AString&& string) noexcept:GenericString<char>(std::move(string)) {}

        AString(const wchar_t* str) {
            add(str);
        }

        AString(const wchar_t* str, size_t length) {
            add(str, length);
        }

        AString(const GenericString<wchar_t>& string) {
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

        AString& operator=(const AString& string) {
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

        inline AString substring(size_t start) const {
            return AString(v + start);
        }

        inline AString substring(size_t start, size_t length) const {
            return AString(v + start, length);
        }

        Array<AString> split(const char* d) const;

        inline AString toLowerCase() const {
            AString copy(*this);
            for (size_t i = 0; i < Length; i++)
                copy.v[i] = (char)tolower(copy.v[i]);
            return copy;
        }

        inline AString toUpperCase() const {
            AString copy(*this);
            for (size_t i = 0; i < Length; i++)
                copy.v[i] = (char)toupper(copy.v[i]);
            return copy;
        }

        inline AString trim() const {
            size_t i, j, l = Length;
            for (i = 0; i < l && isspace(v[i]); i++);
            for (j = l; j > i && isspace(v[j]); j--);
            return AString(v + i, j - i);
        }
    };

}