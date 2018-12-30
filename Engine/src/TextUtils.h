#pragma once

#include "Common.h"

namespace Ghurund {
    inline void toLowerCase(tchar *str) {
        size_t length = _tcslen(str);
        for(size_t i = 0; i < length; i++)
            str[i] = (tchar)_totlower(str[i]);
    }

    inline void toUpperCase(tchar *str) {
        size_t length = _tcslen(str);
        for(size_t i = 0; i < length; i++)
            str[i] = (tchar)_toupper(str[i]);
    }


    inline bool printToBuffer(tchar **buffer, const tchar *format, va_list args) {
        unsigned long result = _vsctprintf(format, args);
        if(result == -1) {
            return false;
        }

        unsigned long length = result + 1;
        *buffer = new tchar[length];

        _vstprintf_s(*buffer, length, format, args);

        return true;
    }

    inline bool printToBuffer(tchar **buffer, const tchar *format, ...) {
        va_list args;
        va_start(args, format);

        bool result = printToBuffer(buffer, format, args);
        va_end(args);
        return result;
    }

    inline void safeCopyStr(char **dest, const char *src) {
        if(src) {
            if(*dest)
                delete[] * dest;
            size_t length = strlen(src) + 1;
            *dest = ghnew char[length];
            if(*dest)
                memcpy(*dest, src, length * sizeof(char));
        } else {
            *dest = nullptr;
        }
    }

    inline void safeCopyStr(wchar_t **dest, const wchar_t *src) {
        if(src) {
            if(*dest)
                delete[] * dest;
            size_t length = wcslen(src) + 1;
            *dest = ghnew wchar_t[length];
            if(*dest)
                memcpy(*dest, src, length * sizeof(wchar_t));
        } else {
            *dest = nullptr;
        }
    }

    inline char *copyStr(const char *src) {
        if(src==nullptr)
            return nullptr;
        size_t length = strlen(src) + 1;
        char *dest = ghnew char[length];
        if(dest)
            memcpy(dest, src, length * sizeof(char));
        return dest;
    }

    inline wchar_t *copyStr(const wchar_t *src) {
        if(src==nullptr)
            return nullptr;
        size_t length = wcslen(src) + 1;
        wchar_t *dest = ghnew wchar_t[length];
        if(dest)
            memcpy(dest, src, length * sizeof(wchar_t));
        return dest;
    }

    inline char *toMultiByte(const wchar_t *src, unsigned int codePage = CP_ACP) {
        int length = (int)wcslen(src);
        int size = WideCharToMultiByte(codePage, 0, src, length, nullptr, 0, nullptr, nullptr);
        if(!size)
            return nullptr;

        char *dest = ghnew char[size + 1];
        WideCharToMultiByte(codePage, 0, src, length + 1, dest, size + 1, nullptr, nullptr);
        return dest;
    }

    inline char *toMultiByte(const char *src, unsigned int codePage = CP_ACP) {
        return copyStr(src);
    }

#ifdef UNICODE
    inline tchar *toTchar(const char *src, unsigned int codePage = CP_ACP) {
        int length = (int)strlen(src);

        int size = MultiByteToWideChar(codePage, 0, src, length, nullptr, 0);
        if(!size)
            return nullptr;

        tchar *dest = ghnew tchar[size + 1];
        MultiByteToWideChar(codePage, 0, src, length + 1, dest, size + 1);
        return dest;
    }

    inline tchar *toTchar(const wchar_t *src, unsigned int codePage = CP_ACP) {
        return copyStr(src);
    }
#else
    inline tchar *toTchar(const wchar_t *src, unsigned int codePage = CP_ACP) {
        int length = (int)wcslen(src);
        int size = WideCharToMultiByte(codePage, 0, src, length, nullptr, 0, nullptr, nullptr);
        if(!size)
            return nullptr;

        tchar *dest = ghnew tchar[size + 1];
        WideCharToMultiByte(codePage, 0, src, length + 1, dest, size + 1, nullptr, nullptr);
        return dest;
    }

    inline tchar *toTchar(const char *src, unsigned int codePage = CP_ACP) {
        return copyStr(src);
    }
#endif

    inline wchar_t *toWideChar(const char *src, unsigned int codePage = CP_ACP) {
        int length = (int)strlen(src);

        int size = MultiByteToWideChar(codePage, 0, src, length, nullptr, 0);
        if(!size)
            return nullptr;

        wchar_t *dest = ghnew wchar_t[size + 1];
        MultiByteToWideChar(codePage, 0, src, length + 1, dest, size + 1);
        return dest;
    }

    inline wchar_t *toWideChar(const wchar_t *src, unsigned int codePage = CP_ACP) {
        return copyStr(src);
    }

    template<class Type> inline size_t lengthOf(Type text);

    template<> inline size_t lengthOf<char*>(char *text) {
        return strlen(text);
    }

    template<> inline size_t lengthOf<wchar_t*>(wchar_t *text) {
        return wcslen(text);
    }

    template<> inline size_t lengthOf<const char*>(const char *text) {
        return strlen(text);
    }

    template<> inline size_t lengthOf<const wchar_t*>(const wchar_t *text) {
        return wcslen(text);
    }

    inline unsigned long hashCode(const wchar_t *str, size_t size = 0) {
        unsigned long h = 0xAAAAAAAA;
        if(!size)
            size = wcslen(str);
        for(unsigned int i = 0; i < size; i++) {
            h ^= ((i & 1) == 0) ? ((h << 7) ^ str[i] * (h >> 3)) :
                (~((h << 11) + str[i] ^ (h >> 5)));
        }
        return h;
    }

    inline unsigned long hashCode(const char *str, size_t size = 0) {
        unsigned long h = 0xAAAAAAAA;
        if(!size)
            size = strlen(str);
        for(unsigned int i = 0; i < size; i++) {
            h ^= ((i & 1) == 0) ? ((h << 7) ^ str[i] * (h >> 3)) :
                (~((h << 11) + str[i] ^ (h >> 5)));
        }
        return h;
    }

}