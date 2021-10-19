#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define _XM_NO_INTRINSICS_
#define _WINSOCKAPI_

#pragma warning (disable : 4521)	// multiple copy constructors specified
#pragma warning (disable : 4238)	// nonstandard extension used : class rvalue used as lvalue

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

#pragma comment(lib, "Dbghelp.lib")

#ifdef _WIN64
#pragma comment(lib, "Ghurund.Core_64.lib")
#else
#pragma comment(lib, "Ghurund.Core_32.lib")
#endif

namespace Ghurund::Core {
    inline static const char* NAMESPACE_NAME = GH_STRINGIFY(Ghurund::Core);

    /**
     * @brief Modifies a value to be in range (alignment*N) <= value < (alignment*(N+1)).
     * @tparam Type type of value, alignment and aligned value.
     * @param value 
     * @param alignment 
     * @return Aligned value
    */
    template<class Type>
    inline Type align(Type value, Type alignment) {
        return (value + alignment - 1) & ~(alignment - 1);
    }

    inline void dumpMemoryLeaks() {
        _CrtDumpMemoryLeaks();
    }

    inline void _____________________checkMemory() {
        _ASSERTE(_CrtCheckMemory());
    }
}