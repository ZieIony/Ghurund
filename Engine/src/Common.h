#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define _XM_NO_INTRINSICS_

#pragma warning (disable : 4521)	// multiple copy constructors specified
#pragma warning (disable : 4238)	// nonstandard extension used : class rvalue used as lvalue

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "Dbghelp.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "D3DCompiler.lib")

#include "windows.h"
#include "stdio.h"
#include "Math.h"
#include "mbctype.h"
#include "tchar.h"

#undef min
#undef max

#include <stdarg.h>
#include <float.h>
#include <crtdbg.h>
#include <stdlib.h>
#include <locale.h>

#ifdef _DEBUG
#define ghnew new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define ghnew new
#endif

typedef TCHAR tchar;
#ifdef _WIN64
typedef DWORD64 address_t;
#else
typedef DWORD address_t;
#endif

#define GH_STRINGIFY(t) #t

namespace Ghurund {
    inline static const char* NAMESPACE_NAME = GH_STRINGIFY(Ghurund);

    inline void dumpMemoryLeaks() {
        _CrtDumpMemoryLeaks();
    }

    inline void _____________________checkMemory() {
        _ASSERTE(_CrtCheckMemory());
    }

    template<class Type> inline Type align(Type value, Type alignment) {
        return (value + alignment - 1) & ~(alignment - 1);
    }
}