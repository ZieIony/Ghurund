#pragma once

#include "GenericStringView.h"

namespace Ghurund::Core {

#ifdef UNICODE
    typedef GenericStringView<wchar_t> StringView;
#else
    typedef GenericStringView<char> StringView;
#endif

    typedef GenericStringView<wchar_t> WStringView;
    typedef GenericStringView<char> AStringView;
    typedef GenericStringView<tchar> TStringView;
}