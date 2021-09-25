#pragma once

#include "GenericString.h"

namespace Ghurund::Core {

#ifdef UNICODE
    typedef GenericString<wchar_t> String;
#else
    typedef GenericString<char> String;
#endif

    typedef GenericString<wchar_t> WString;
    typedef GenericString<char> AString;
    typedef GenericString<tchar> TString;
}