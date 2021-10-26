#pragma once

#include "Ghurund.Core.h"

#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

#ifdef _DEBUG
#ifdef _WIN64
#pragma comment(lib, "tinyxml2d64.lib")
#else
#pragma comment(lib, "tinyxml2d.lib")
#endif
#else
#ifdef _WIN64
#pragma comment(lib, "tinyxml264.lib")
#else
#pragma comment(lib, "tinyxml2.lib")
#endif
#endif

#ifdef _WIN64
#pragma comment(lib, "Ghurund.UI_64.lib")
#else
#pragma comment(lib, "Ghurund.UI_32.lib")
#endif