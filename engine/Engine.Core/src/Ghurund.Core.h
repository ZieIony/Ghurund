#pragma once

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "Pathcch.lib")

#ifdef _WIN64
#pragma comment(lib, "Ghurund.Core_64.lib")
#else
#pragma comment(lib, "Ghurund.Core_32.lib")
#endif