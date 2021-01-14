#include "Ghurund.h"

#include "TestApplication.h"

#include "Dxgi1_6.h"
#include <dxgidebug.h>

#ifdef _WIN64
#pragma comment(lib, "GhurundEngine.Core_64.lib")
#pragma comment(lib, "GhurundEngine_64.lib")
#else
#pragma comment(lib, "GhurundEngine.Core_32.lib")
#pragma comment(lib, "GhurundEngine_32.lib")
#endif


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    _____________________checkMemory();

    Logger::init();
    Logger::log(LogType::INFO, "working dir: {}\n", DirectoryPath(L".").AbsolutePath);

    HANDLE singleInstanceMutex = CreateMutex(nullptr, true, "Ghurund::Game");
    bool alreadyRunning = GetLastError() == ERROR_ALREADY_EXISTS;

    if (alreadyRunning) {
        MessageBox(nullptr, _T("Application is already running."), "Ghurund::Game", MB_OK | MB_ICONEXCLAMATION);
    } else {
        TestApplication application;
        Settings settings;
        settings.parse(cmdLine);
        application.run(&settings);
    }

    CloseHandle(singleInstanceMutex);

    Logger::uninit();

#ifdef _DEBUG
    _____________________checkMemory();
#endif
    return 0;
}