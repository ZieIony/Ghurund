#pragma once

#include "Ghurund.UI.h"

#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

#ifdef _WIN64
#pragma comment(lib, "Ghurund.UI.DirectX_64.lib")
#else
#pragma comment(lib, "Ghurund.UI.DirectX_32.lib")
#endif