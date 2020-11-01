#pragma once

#undef GDIPVER
#define GDIPVER     0x0110

namespace Gdiplus {
    class Graphics;
}

#include <algorithm>
#include <objidl.h>

#undef min
#undef max

#include <gdiplus.h>

#pragma comment (lib, "Gdiplus.lib")
