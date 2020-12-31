#pragma once

#include "WString.h"
#include "AString.h"

namespace Ghurund {

#ifdef UNICODE
    typedef WString String;
#else
    typedef AString String;
#endif
}