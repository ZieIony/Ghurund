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

#ifdef _WIN64
#pragma comment(lib, "GhurundEngine.Core_64.lib")
#pragma comment(lib, "GhurundEngine.UI_64.lib")
#pragma comment(lib, "GhurundEngine_64.lib")
#else
#pragma comment(lib, "GhurundEngine.Core_32.lib")
#pragma comment(lib, "GhurundEngine.UI_32.lib")
#pragma comment(lib, "GhurundEngine_32.lib")
#endif

namespace Ghurund {
    template<Derived<Application> Type>
    static void main(const Ghurund::Settings& settings = Ghurund::Settings(), std::unique_ptr<LogOutput> logOutput = nullptr) {
#ifdef _DEBUG
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
        _____________________checkMemory();
#endif

        Logger::init(std::move(logOutput));
#ifdef _DEBUG
        Logger::log(LogType::INFO, _T("working dir: {}\n"), Ghurund::DirectoryPath(L".").AbsolutePath);
#endif

        {
            Type application;
            application.run(&settings);
        }

#ifdef _DEBUG
        Pointer::dumpPointers();
#endif

        Logger::uninit();

#ifdef _DEBUG
        _____________________checkMemory();
#endif
    }

    template<Derived<Application> Type>
    static void main(
        const String& instanceName,
        const Ghurund::Settings& settings = Ghurund::Settings(),
        std::unique_ptr<LogOutput> logOutput = nullptr
    ) {
        HANDLE singleInstanceMutex = CreateMutex(nullptr, true, instanceName.Data);
        bool alreadyRunning = GetLastError() == ERROR_ALREADY_EXISTS;

        if (alreadyRunning) {
            MessageBox(nullptr, _T("Application is already running."), instanceName.Data, MB_OK | MB_ICONEXCLAMATION);
        } else {
            main<Type>(settings, std::move(logOutput));
        }

        CloseHandle(singleInstanceMutex);
    }
}