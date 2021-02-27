#pragma once

#include "Common.h"
#include <Windows.h>

#include "core/string/String.h"
#include "core/string/TextUtils.h"

namespace Ghurund {
    inline char* toMultiByte(const wchar_t* src, unsigned int codePage = CP_ACP) {
        int length = (int)wcslen(src);
        int size = WideCharToMultiByte(codePage, 0, src, length, nullptr, 0, nullptr, nullptr);
        if (!size)
            return nullptr;

        char* dest = ghnew char[size + 1];
        WideCharToMultiByte(codePage, 0, src, length + 1, dest, (int)(size + 1), nullptr, nullptr);
        return dest;
    }

    inline char* toMultiByte(const char* src, unsigned int codePage = CP_ACP) {
        return copyStr(src);
    }

    inline AString toMultiByte(const WString& src, unsigned int codePage = CP_ACP) {
        int size = WideCharToMultiByte(codePage, 0, src.Data, (int)src.Length, nullptr, 0, nullptr, nullptr);
        if (!size)
            return nullptr;

        char* dest = ghnew char[size + 1];
        WideCharToMultiByte(codePage, 0, src.Data, (int)src.Size, dest, (int)(size + 1), nullptr, nullptr);
        AString str = dest;
        delete[] dest;
        return str;
    }

    inline AString toMultiByte(const AString& src, unsigned int codePage = CP_ACP) {
        return AString(src);
    }

#ifdef UNICODE
    inline tchar* toTchar(const char* src, unsigned int codePage = CP_ACP) {
        int length = (int)strlen(src);

        int size = MultiByteToWideChar(codePage, 0, src, length, nullptr, 0);
        if (!size)
            return nullptr;

        tchar* dest = ghnew tchar[size + 1];
        MultiByteToWideChar(codePage, 0, src, length + 1, dest, (int)(size + 1));
        return dest;
    }

    inline tchar* toTchar(const wchar_t* src, unsigned int codePage = CP_ACP) {
        return copyStr(src);
    }

    inline String toTchar(const WString& src, unsigned int codePage = CP_ACP) {
        return String(src);
    }

    inline String toTchar(const AString& src, unsigned int codePage = CP_ACP) {
        return toWideChar(src);
    }
#else
    inline tchar* toTchar(const wchar_t* src, unsigned int codePage = CP_ACP) {
        int length = (int)wcslen(src);
        int size = WideCharToMultiByte(codePage, 0, src, length, nullptr, 0, nullptr, nullptr);
        if (!size)
            return nullptr;

        tchar* dest = ghnew tchar[size + 1];
        WideCharToMultiByte(codePage, 0, src, length + 1, dest, (int)(size + 1), nullptr, nullptr);
        return dest;
    }

    inline tchar* toTchar(const char* src, unsigned int codePage = CP_ACP) {
        return copyStr(src);
    }

    inline String toTchar(const WString& src, unsigned int codePage = CP_ACP) {
        return toMultiByte(src);
    }

    inline String toTchar(const AString& src, unsigned int codePage = CP_ACP) {
        return String(src);
    }
#endif

    inline wchar_t* toWideChar(const char* src, unsigned int codePage = CP_ACP) {
        int length = (int)strlen(src);

        int size = MultiByteToWideChar(codePage, 0, src, length, nullptr, 0);
        if (!size)
            return nullptr;

        wchar_t* dest = ghnew wchar_t[size + 1];
        MultiByteToWideChar(codePage, 0, src, length + 1, dest, (int)(size + 1));
        return dest;
    }

    inline WString toWideChar(const WString& src, unsigned int codePage = CP_ACP) {
        return WString(src);
    }

    inline WString toWideChar(const AString& src, unsigned int codePage = CP_ACP) {
        int size = MultiByteToWideChar(codePage, 0, src.Data, (int)src.Length, nullptr, 0);
        if (!size)
            return nullptr;

        wchar_t* dest = ghnew wchar_t[size + 1];
        MultiByteToWideChar(codePage, 0, src.Data, (int)src.Size, dest, (int)(size + 1));
        WString str = dest;
        delete[] dest;
        return str;
    }

    inline wchar_t* toWideChar(const wchar_t* src, unsigned int codePage = CP_ACP) {
        return copyStr(src);
    }

}