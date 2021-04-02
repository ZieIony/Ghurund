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

        std::strong_ordering operator<=>(const AString& string) const;

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