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
	
	Logger::init(LogOutput::SYSTEM_CONSOLE);
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
    return 0;
}