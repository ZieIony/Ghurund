#pragma once

#include "GenericString.h"

#include <format>

namespace Ghurund::Core {

#ifdef UNICODE
    typedef GenericString<wchar_t> String;
#else
    typedef GenericString<char> String;
#endif

    typedef GenericString<wchar_t> WString;
    typedef GenericString<char> AString;
    typedef GenericString<tchar> TString;

    template<typename T>
    String toString(const T& obj) = delete;

    template <class T>
    concept StringConvertible = requires(T obj) {
        { toString(obj) } -> std::same_as<String>;
    };
}