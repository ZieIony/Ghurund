#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define _XM_NO_INTRINSICS_

#undef min
#undef max

#pragma warning (disable : 4521)	// multiple copy constructors specified
#pragma warning (disable : 4238)	// nonstandard extension used : class rvalue used as lvalue

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "Dbghelp.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "D3DCompiler.lib")

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include "stdlib.h"
#include "crtdbg.h"
#endif

#include "windows.h"
#include "stdio.h"
#include "Math.h"
#include "mbctype.h"
#include "tchar.h"
#include <memory>

#ifdef _DEBUG
#define ghnew new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define ghnew new
#endif

typedef TCHAR tchar;
#ifdef _WIN64
typedef DWORD64 address_t;
#else
typedef DWORD address_t;
#endif

template<class Type> inline Type lerp(Type val1, Type val2, float fact) {
    return (1 - fact)*val1 + fact*val2;
}

namespace Ghurund {
    enum class Status {
        OK, INV_PARAM, INV_STATE, CALL_FAIL, SOCKET, IO, NOT_IMPLEMENTED, ALREADY_LOADED, UNKNOWN,

        WRONG_RESOURCE_VERSION,
        WRONG_RESOURCE_TYPE,
        FILE_DOESNT_EXIST,
        FILE_EXISTS,
        UNKNOWN_FORMAT,

        COMPILATION_ERROR,

        DIRECTX12_NOT_SUPPORTED
    };

    template<class Type> inline Type minMax(Type a, Type b, Type c) {
        if(b < a)
            return a;
        if(b > c)
            return c;
        return b;
    }
    template<class Type> inline Type round(Type a) {
        return floor(a + (Type)0.5);
    }
    template<class Type> inline Type frac(Type a) {
        float a2 = abs(a);
        return a2 - floor(a2);
    }

    inline void dumpMemoryLeaks() {
        _CrtDumpMemoryLeaks();
    }

    inline void _____________________checkMemory() {
        _ASSERTE(_CrtCheckMemory());
    }

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

    inline float random() {
        return (float)rand() / (float)RAND_MAX;
    }

    template<class Type> inline Type align(Type value, Type alignment) {
        return (value + alignment-1) & ~(alignment-1);
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

    inline void safeCopyStrA(char **dest, const char *src) {
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

    inline void safeCopyStrW(wchar_t **dest, const wchar_t *src) {
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

#ifdef UNICODE
#define safeCopyStr(a,b) safeCopyStrW(a,b)
#else
#define safeCopyStr(a,b) safeCopyStrA(a,b)
#endif

    inline char *copyStrA(const char *src) {
        if(src==nullptr)
            return nullptr;
        size_t length = strlen(src) + 1;
        char *dest = ghnew char[length];
        if(dest)
            memcpy(dest, src, length * sizeof(char));
        return dest;
    }

    inline wchar_t *copyStrW(const wchar_t *src) {
        if(src==nullptr)
            return nullptr;
        size_t length = wcslen(src) + 1;
        wchar_t *dest = ghnew wchar_t[length];
        if(dest)
            memcpy(dest, src, length * sizeof(wchar_t));
        return dest;
    }

#ifdef UNICODE
#define copyStr(a) copyStrW(a)
#else
#define copyStr(a) copyStrA(a)
#endif

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
        return copyStrA(src);
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
        return copyStrW(src);
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

    inline tchar *toMultiByte(const char *src, unsigned int codePage = CP_ACP) {
        return copyStrA(src);
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
        return copyStrW(src);
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

    template<class Type> void safeDelete(Type **p) {
        delete *p;
        *p = nullptr;
    }

    template<class Type> void safeDeleteArray(Type *p) {
        delete[] *p;
        *p = nullptr;
    }

}