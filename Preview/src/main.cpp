#include "Ghurund.h"
#include "core/io/DirectoryPath.h"

#include "PreviewApplication.h"

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
    Logger::log(LogType::INFO, _T("working dir: {}\n"), Ghurund::DirectoryPath(L".").AbsolutePath);

    HANDLE singleInstanceMutex = CreateMutex(nullptr, true, _T("Preview::PreviewApplication"));
    bool alreadyRunning = GetLastError() == ERROR_ALREADY_EXISTS;

    if (alreadyRunning) {
        MessageBox(nullptr, _T("Application is already running."), _T("Preview::PreviewApplication"), MB_OK | MB_ICONEXCLAMATION);
    } else {
        Preview::PreviewApplication application;
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