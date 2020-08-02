#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define _XM_NO_INTRINSICS_

#undef min
#undef max

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

#include "Status.h"
#include "core/Enum.h"
#include "core/Noncopyable.h"
#include "core/threading/CriticalSection.h"
#include "core/string/String.h"

#include "fmt/core.h"
#ifdef _DEBUG
#pragma comment(lib, "fmtd.lib")
#else
#pragma comment(lib, "fmt.lib")
#endif

#include "TestApplication.h"

#include "Dxgi1_6.h"
#include <dxgidebug.h>

#ifdef _WIN64
#pragma comment(lib, "GhurundEngine_64.lib")
#else
#pragma comment(lib, "GhurundEngine_32.lib")
#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	_____________________checkMemory();
	
	Logger::init();
    Logger::log(LogType::INFO, String("working dir: ") + DirectoryPath(".").getAbsolutePath());

    {
        TestApplication application;
        Settings settings;
        settings.parse(cmdLine);
        application.run(&settings);
    }

    Logger::uninit();

#ifdef _DEBUG
    _____________________checkMemory();
    ComPtr<IDXGIDebug> debugInterface;
    if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debugInterface))))
        debugInterface->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
#endif
    fmt::print("{}", 42);
    return 0;
}