#pragma once

#include "Common.h"
#include "core/application/Application.h"
#include "core/logging/Logger.h"

#include <Windows.h>
#include <format>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "Pathcch.lib")

namespace Ghurund::Core {
    template<Derived<Application> Type>
    static void main(const Settings* settings = nullptr, std::unique_ptr<LogOutput> logOutput = nullptr) {
#ifdef _DEBUG
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
        _____________________checkMemory();
#endif

        Logger::init(std::move(logOutput));
#ifdef _DEBUG
        auto text = std::format(_T("working dir: {}\n"), DirectoryPath(L".").AbsolutePath);
        Logger::log(LogType::INFO, text.c_str());
#endif

		try {
			Type application = {};
			application.run(settings);
		} catch (const std::exception& e) {
			auto message = std::format("Un uncaught {} has been thrown: \"{}\". Check logs for more info.", typeid(e).name(), e.what());
			MessageBoxA(nullptr, message.c_str(), "Error", MB_OK);
		} catch (...) {
			MessageBoxA(nullptr, "Unknown error. Check logs for more info.", "Error", MB_OK);
		}

#ifdef _DEBUG
        RefCountedObject::dumpPointers();
#endif

        Logger::uninit();

#ifdef _DEBUG
        _____________________checkMemory();
#endif
    }

    template<Derived<Application> Type>
    static void main(
        const String& instanceName,
        const Settings* settings = nullptr,
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