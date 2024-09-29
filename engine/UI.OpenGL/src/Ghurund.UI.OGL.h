#pragma once

#include "Ghurund.UI.h"

#pragma comment(lib, "Kernel32.lib")

#ifdef _WIN64
#pragma comment(lib, "Ghurund.UI.OpenGL_64.lib")
#else
#pragma comment(lib, "Ghurund.UI.OpenGL_32.lib")
#endif