#pragma once

#include "Common.h"

#include <tchar.h>
#include <ctype.h>

namespace Ghurund {
    inline void toLowerCase(tchar* str) {
        size_t length = _tcslen(str);
        for (size_t i = 0; i < length; i++)
            str[i] = (tchar)_totlower(str[i]);
    }

    inline void toUpperCase(tchar* str) {
        size_t length = _tcslen(str);
        for (size_t i = 0; i < length; i++)
            str[i] = (tchar)_toupper(str[i]);
    }

    inline void safeCopyStr(char** dest, const char* src) {
        if (src) {
            if (*dest)
                delete[] * dest;
            size_t length = strlen(src) + 1;
            *dest = ghnew char[length];
            if (*dest)
                memcpy(*dest, src, length * sizeof(char));
        } else {
            *dest = nullptr;
        }
    }

    inline void safeCopyStr(wchar_t** dest, const wchar_t* src) {
        if (src) {
            if (*dest)
                delete[] * dest;
            size_t length = wcslen(src) + 1;
            *dest = ghnew wchar_t[length];
            if (*dest)
                memcpy(*dest, src, length * sizeof(wchar_t));
        } else {
            *dest = nullptr;
        }
    }

    inline char* copyStr(const char* src) {
        if (src == nullptr)
            return nullptr;
        size_t length = strlen(src) + 1;
        char* dest = ghnew char[length];
        if (dest)
            memcpy(dest, src, length * sizeof(char));
        return dest;
    }

    inline char* copyStr(const char* src, size_t length) {
        if (src == nullptr)
            return nullptr;
        char* dest = ghnew char[length];
        if (dest)
            memcpy(dest, src, length * sizeof(char));
        return dest;
    }

    inline wchar_t* copyStr(const wchar_t* src) {
        if (src == nullptr)
            return nullptr;
        size_t length = wcslen(src) + 1;
        wchar_t* dest = ghnew wchar_t[length];
        if (dest)
            memcpy(dest, src, length * sizeof(wchar_t));
        return dest;
    }

    inline wchar_t* copyStr(const wchar_t* src, size_t length) {
        if (src == nullptr)
            return nullptr;
        wchar_t* dest = ghnew wchar_t[length];
        if (dest)
            memcpy(dest, src, length * sizeof(wchar_t));
        return dest;
    }

    inline size_t lengthOf(char* text) {
        return strlen(text);
    }

    inline size_t lengthOf(wchar_t* text) {
        return wcslen(text);
    }

    inline size_t lengthOf(const char* text) {
        return strlen(text);
    }

    inline size_t lengthOf(const wchar_t* text) {
        return wcslen(text);
    }

    inline unsigned long hashCode(const wchar_t* str, size_t size = 0) {
        unsigned long h = 0xAAAAAAAA;
        if (!size)
            size = wcslen(str);
        for (unsigned int i = 0; i < size; i++) {
            h ^= ((i & 1) == 0) ? ((h << 7) ^ str[i] * (h >> 3)) :
                (~((h << 11) + str[i] ^ (h >> 5)));
        }
        return h;
    }

    inline unsigned long hashCode(const char* str, size_t size = 0) {
        unsigned long h = 0xAAAAAAAA;
        if (!size)
            size = strlen(str);
        for (unsigned int i = 0; i < size; i++) {
            h ^= ((i & 1) == 0) ? ((h << 7) ^ str[i] * (h >> 3)) :
                (~((h << 11) + str[i] ^ (h >> 5)));
        }
        return h;
    }

}