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

        std::strong_ordering operator<=>(const WString& string) const;

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