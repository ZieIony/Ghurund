#pragma once

#include "application/Application.h"

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "Dbghelp.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "tinyxml2.lib")

#ifdef _DEBUG
#pragma comment(lib, "fmtd.lib")
#else
#pragma comment(lib, "fmt.lib")
#endif

namespace Ghurund {
    inline void dumpMemoryLeaks() {
        _CrtDumpMemoryLeaks();
    }

    inline void _____________________checkMemory() {
        _ASSERTE(_CrtCheckMemory());
    }
}