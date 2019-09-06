#pragma once

#include "UnicodeString.h"
#include "ASCIIString.h"

namespace Ghurund {

#ifdef UNICODE
    typedef UnicodeString String;
    typedef UnicodeString S;
#else
    typedef ASCIIString String;
    typedef ASCIIString S;
#endif

    typedef UnicodeString U;
    typedef ASCIIString A;

}