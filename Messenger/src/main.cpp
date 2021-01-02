#include "Ghurund.h"
#include "core/io/DirectoryPath.h"

#include "MessengerApplication.h"

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
    Logger::log(LogType::INFO, _T("working dir: {}\n"), DirectoryPath(L".").AbsolutePath);

    Messenger::MessengerApplication application;
    Settings settings;
    settings.parse(cmdLine);
    application.run(&settings);

    Logger::uninit();

#ifdef _DEBUG
    _____________________checkMemory();
#endif
    return 0;
}