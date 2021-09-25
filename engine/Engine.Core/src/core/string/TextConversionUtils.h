#pragma once

#include "Common.h"

#include "core/string/String.h"

namespace Ghurund::Core {
    template<typename FromChar, typename ToChar>
    inline ToChar* convertText(const FromChar* src, unsigned int codePage = CP_ACP) {
        return nullptr;
    }

    template<typename FromChar, typename ToChar>
    inline GenericString<ToChar> convertText(const GenericString<FromChar>& src, unsigned int codePage = CP_ACP) {
        return GenericString<ToChar>();
    }

    template<>
    inline char* convertText(const wchar_t* src, unsigned int codePage) {
        int length = (int)wcslen(src);
        int size = WideCharToMultiByte(codePage, 0, src, length, nullptr, 0, nullptr, nullptr);
        if (!size)
            return nullptr;

        char* dest = ghnew char[size + 1];
        WideCharToMultiByte(codePage, 0, src, length + 1, dest, (int)(size + 1), nullptr, nullptr);
        return dest;
    }

    template<>
    inline char* convertText(const char* src, unsigned int codePage) {
        return copyStr(src);
    }

    template<>
    inline AString convertText(const WString& src, unsigned int codePage) {
        int size = WideCharToMultiByte(codePage, 0, src.Data, (int)src.Length, nullptr, 0, nullptr, nullptr);
        if (!size)
            return AString();

        char* dest = ghnew char[size + 1];
        WideCharToMultiByte(codePage, 0, src.Data, (int)src.Size, dest, (int)(size + 1), nullptr, nullptr);
        AString str = dest;
        delete[] dest;
        return str;
    }

    template<>
    inline AString convertText(const AString& src, unsigned int codePage) {
        return AString(src);
    }

    template<>
    inline wchar_t* convertText(const char* src, unsigned int codePage) {
        int length = (int)strlen(src);

        int size = MultiByteToWideChar(codePage, 0, src, length, nullptr, 0);
        if (!size)
            return nullptr;

        wchar_t* dest = ghnew wchar_t[size + 1];
        MultiByteToWideChar(codePage, 0, src, length + 1, dest, (int)(size + 1));
        return dest;
    }

    template<>
    inline WString convertText(const WString& src, unsigned int codePage) {
        return WString(src);
    }

    template<>
    inline WString convertText(const AString& src, unsigned int codePage) {
        int size = MultiByteToWideChar(codePage, 0, src.Data, (int)src.Length, nullptr, 0);
        if (!size)
            return WString();

        wchar_t* dest = ghnew wchar_t[size + 1];
        MultiByteToWideChar(codePage, 0, src.Data, (int)src.Size, dest, (int)(size + 1));
        WString str = dest;
        delete[] dest;
        return str;
    }

    template<>
    inline wchar_t* convertText(const wchar_t* src, unsigned int codePage) {
        return copyStr(src);
    }
}