#pragma once

#include "AStringView.h"
#include "WStringView.h"

namespace Ghurund {
#ifdef UNICODE
    typedef WStringView StringView;
#else
    typedef AStringView StringView;
#endif
}