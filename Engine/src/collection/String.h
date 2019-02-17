#pragma once

#include "UnicodeString.h"
#include "ASCIIString.h"

namespace Ghurund {

#ifdef UNICODE
    typedef UnicodeString String;
#else
    typedef ASCIIString String;
#endif

}