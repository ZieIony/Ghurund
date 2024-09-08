#pragma once

#include "Common.h"

#include <ctype.h>
#include <tchar.h>
#include <Windows.h>

namespace Ghurund::Core {
    template<typename CharType>
    inline bool isSpace(CharType c) {
        return false;
    }

    template<>
    inline bool isSpace(char c) {
        return isspace(c);
    }

    template<>
    inline bool isSpace(wchar_t c) {
        return iswspace(c);
    }

    template<typename CharType>
    inline size_t lengthOf(const CharType* text) {
        return 0;
    }

    template<>
    inline size_t lengthOf(const char* text) {
        return strlen(text);
    }

    template<>
    inline size_t lengthOf(const wchar_t* text) {
        return wcslen(text);
    }

    template<typename CharType>
    inline CharType toLowerCase(CharType c) {}

    template<>
    inline char toLowerCase(char c) {
        return (char)tolower(c);
    }

    template<>
    inline wchar_t toLowerCase(wchar_t c) {
        return (wchar_t)towlower(c);
    }

    template<typename CharType>
    inline void toLowerCase(CharType* str) {
        size_t length = lengthOf<CharType>(str);
        for (size_t i = 0; i < length; i++)
            str[i] = toLowerCase<CharType>(str[i]);
    }

    template<typename CharType>
    inline CharType toUpperCase(CharType str) {}

    template<>
    inline char toUpperCase(char c) {
        return (char)toupper(c);
    }

    template<>
    inline wchar_t toUpperCase(wchar_t c) {
        return (wchar_t)towupper(c);
    }

    template<typename CharType>
    inline void toUpperCase(CharType* str) {
        size_t length = lengthOf<CharType>(str);
        for (size_t i = 0; i < length; i++)
            str[i] = (char)toUpperCase<CharType>(str[i]);
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

    template<typename CharType>
    inline int lexicographicalStrCompare(const CharType* str1, const CharType* str2) {
        return 0;
    }

    template<>
    inline int lexicographicalStrCompare(const char* str1, const char* str2) {
        return lstrcmpA(str1, str2);
    }

    template<>
    inline int lexicographicalStrCompare(const wchar_t* str1, const wchar_t* str2) {
        return lstrcmpW(str1, str2);
    }
}