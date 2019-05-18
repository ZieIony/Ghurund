#include "Logger.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <process.h>
#include "dbghelp.h"
#include "collection/String.h"

namespace Ghurund {
    const LogType& LogType::INFO = LogType(LogTypeEnum::INFO, _T("INFO"));
    const LogType& LogType::WARNING = LogType(LogTypeEnum::WARNING, _T("WARNING"));
    const LogType& LogType::ERR0R = LogType(LogTypeEnum::ERR0R, _T("ERROR"));

    HANDLE Logger::debugOutput;
    HANDLE Logger::file;
    LogOutput Logger::output;
    HANDLE Logger::process;
    SYMBOL_INFO* Logger::symbol;
    IMAGEHLP_LINE Logger::line;
    CriticalSection Logger::criticalSection;
    std::function<void(const tchar*)> Logger::onLogged;

    address_t Logger::getAddress() {
        constexpr int frames = 1;
        void* stack;
        WORD numberOfFrames = CaptureStackBackTrace(3, frames, &stack, NULL);

        return (address_t)stack;
    }

    String Logger::getFileLine(address_t address) {
        tchar* buffer = nullptr;

        DWORD64 displacement = 0;
        if (!SymFromAddr(process, address, &displacement, symbol)) {
            printToBuffer(&buffer, _T("[%p]: "), address);
            goto cleanUp;
        }

        DWORD displacement2 = 0;
        if (!SymGetLineFromAddr(process, address, &displacement2, &line)) {
            printToBuffer(&buffer, _T("[%p:%hs]: "), address, symbol->Name);
            goto cleanUp;
        }

        printToBuffer(&buffer, _T("%hs(%lu): [0x%p %hs(..)] "), line.FileName, line.LineNumber, address, symbol->Name);

    cleanUp:
        String str(buffer);
        delete[] buffer;
        return str;
    }

    void Logger::writeLog(const tchar* str, size_t length) {
        criticalSection.enter();
        switch (output) {
        case LogOutput::CUSTOM_CONSOLE:
            WriteConsole(debugOutput, str, length, nullptr, nullptr);
            break;
        case LogOutput::SYSTEM_CONSOLE:
            OutputDebugString(str);
            break;
        case LogOutput::FILE:
            unsigned long bytes;
            WriteFile(file, str, length * sizeof(tchar), &bytes, nullptr);
            break;
        case LogOutput::CUSTOM_CALLBACK:
            onLogged(str);
            break;
        }
        criticalSection.leave();
    }

    void Logger::logVA(const LogType& type, const String& format, va_list args) {
        String log(getFileLine(getAddress()));

        log.add(type.Name);
        log.add(" ");

        tchar* buffer = nullptr;
        if (!printToBuffer(&buffer, format, args))
            goto cleanUp;
        log.add(buffer);

        if (!log.endsWith(_T("\n")))
            log.add(_T("\n"));

        writeLog(log, log.Length);

    cleanUp:
        delete[] buffer;
    }

    void Logger::log(const LogType& type, const tchar* format, ...) {
        va_list args;
        va_start(args, format);

        logVA(type, format, args);

        va_end(args);
    }

    Status Logger::log(const LogType& type, const Status status, const tchar* format, ...) {
        va_list args;
        va_start(args, format);

        logVA(type, format, args);

        va_end(args);

        return status;
    }

    void Logger::init(LogOutput output, const tchar* name, std::function<void(const tchar*)> onLogged) {
        Logger::output = output;

        if (symbol == nullptr) {
            constexpr int frames = 1;
            process = GetCurrentProcess();
            SymInitialize(process, NULL, TRUE);

            constexpr int symbolStructSize = sizeof(SYMBOL_INFO) + (MAX_SYM_NAME - 1) * sizeof(tchar);
            symbol = (SYMBOL_INFO*)(ghnew char[symbolStructSize]);
            symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
            symbol->MaxNameLen = MAX_SYM_NAME;

            line.SizeOfStruct = sizeof(IMAGEHLP_LINE);
        }

        switch (output) {
        case LogOutput::CUSTOM_CONSOLE:
        {
            AllocConsole();
            SetConsoleTitle(name != nullptr ? name : _T("Debug Window"));
            debugOutput = GetStdHandle(STD_OUTPUT_HANDLE);
            COORD co = {80,25};
            SetConsoleScreenBufferSize(debugOutput, co);
        }
        break;
        case LogOutput::SYSTEM_CONSOLE:
#ifdef UNICODE
            //_setmode(_fileno(stdout), _O_U16TEXT);
            SetConsoleOutputCP(65001);
#endif
            break;
        case LogOutput::FILE:
            file = CreateFile(name != nullptr ? name : _T("Ghurund.log"), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
            break;
        case LogOutput::CUSTOM_CALLBACK:
            Logger::onLogged = onLogged;
            break;
        }
    }

    void Logger::uninit() {
        if (symbol != nullptr) {
            delete[] symbol;
            SymCleanup(process);
        }

        switch (output) {
        case LogOutput::CUSTOM_CONSOLE:
            FreeConsole();
            break;
        case LogOutput::SYSTEM_CONSOLE:
            break;
        case LogOutput::FILE:
            CloseHandle(file);
            break;
        }
    }
}