#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define _XM_NO_INTRINSICS_
#define _WINSOCKAPI_

#pragma warning (disable : 4521)	// multiple copy constructors specified
#pragma warning (disable : 4238)	// nonstandard extension used : class rvalue used as lvalue

#include <stdint.h>

#ifdef _DEBUG
#include <crtdbg.h>
#define ghnew new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define ghnew new
#endif

#ifdef UNICODE
typedef wchar_t tchar;
#else
typedef char tchar;
#endif

#ifdef _WIN64
typedef unsigned __int64 address_t;
#else
typedef unsigned long address_t;
#endif

#define GH_STRINGIFY(t) #t

namespace Ghurund {
    inline static const char* NAMESPACE_NAME = GH_STRINGIFY(Ghurund);

    template<class Type> inline Type align(Type value, Type alignment) {
        return (value + alignment - 1) & ~(alignment - 1);
    }

    inline void dumpMemoryLeaks() {
        _CrtDumpMemoryLeaks();
    }

    inline void _____________________checkMemory() {
        _ASSERTE(_CrtCheckMemory());
    }
}