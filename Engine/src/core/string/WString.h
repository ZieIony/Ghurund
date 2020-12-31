#pragma once

#include "GenericString.h"
#include "core/collection/Array.h"

namespace Ghurund {

    class WString: public GenericString<wchar_t> {
    public:
        using GenericString<wchar_t>::GenericString;

        WString() {}

        WString(const WString& string):GenericString<wchar_t>(string) {}

        WString(WString&& string) noexcept:GenericString<wchar_t>(std::move(string)) {}

        WString(const char* str) {
            add(str);
        }

        WString(const char* str, size_t length) {
            add(str, length);
        }

        WString(const GenericString<char>& string) {
            add(string.getData());
        }

        using GenericString<wchar_t>::add;

        void add(const char e);

        inline void add(const char* str) {
            if (!str)
                return;
            wchar_t* wstr = toWideChar(str);
            add(wstr);
            delete[] wstr;
        }

        inline void add(const char* str, size_t len) {
            if (!str)
                return;
            wchar_t* wstr = toWideChar(str);
            add(wstr, len);
            delete[] wstr;
        }

        using GenericString<wchar_t>::operator==;

        bool operator==(const char* str) const {
            if (!str)
                return false;
            wchar_t* wstr = toWideChar(str);
            bool result = memcmp(v, wstr, Length * sizeof(wchar_t)) == 0;
            delete[] wstr;
            return result;
        }

        using GenericString<wchar_t>::operator=;

        WString& operator=(const WString& string) {
            size = string.size;
            initial = string.initial;
            capacity = string.capacity;
            wchar_t* prevV = v;
            wchar_t* stringV = string.v;
            v = new wchar_t[capacity];
            memcpy(v, stringV, size * sizeof(wchar_t));
            hash = string.hash;
            delete[] prevV;
            return *this;
        }

        inline WString substring(size_t start) const {
            return WString(v + start);
        }

        inline WString substring(size_t start, size_t length) const {
            return WString(v + start, length);
        }

        Array<WString> split(const wchar_t* d) const;

        inline WString toLowerCase() {
            WString copy(*this);
            for (size_t i = 0; i < Length; i++)
                copy.v[i] = (wchar_t)towlower(copy.v[i]);
            return copy;
        }

        inline WString toUpperCase() const {
            WString copy(*this);
            for (size_t i = 0; i < Length; i++)
                copy.v[i] = (wchar_t)towupper(copy.v[i]);
            return copy;
        }

        inline WString trim() const {
            size_t i, j, l = Length;
            for (i = 0; i < l && iswspace(v[i]); i++);
            for (j = l; j > i && iswspace(v[j]); j--);
            return WString(v + i, j - i);
        }
    };

}