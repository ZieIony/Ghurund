#pragma once

#include "Ghurund.UI.h"

#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")

#ifdef _WIN64
#pragma comment(lib, "Ghurund.UI.GDI_64.lib")
#else
#pragma comment(lib, "Ghurund.UI.GDI_32.lib")
#endif