#include "application/log/Logger.h"

#include "core/string/String.h"
#include "Common.h"

#include "dbghelp.h"

#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <process.h>

namespace Ghurund {
    using namespace std;

    HANDLE Logger::process = {};
    SYMBOL_INFO* Logger::symbol = nullptr;
    IMAGEHLP_LINE Logger::line;
    CriticalSection Logger::criticalSection;
    LogType Logger::filterLevel = LogType::INFO;
    LogOutput* Logger::logOutput = nullptr;

    address_t Logger::getAddress() {
        constexpr int frames = 1;
        void* stack;
        WORD numberOfFrames = CaptureStackBackTrace(3, frames, &stack, NULL);

        return (address_t)stack;
    }

    string Logger::getFileLine(address_t address) {
        DWORD64 displacement = 0;
        if (!SymFromAddr(process, address, &displacement, symbol))
            return fmt::format(_T("[{}]: "), address);

        DWORD displacement2 = 0;
        if (!SymGetLineFromAddr(process, address, &displacement2, &line))
            return fmt::format(_T("[{}:{}]: "), address, symbol->Name);

        return fmt::format(_T("{0}({1:d}): [{2:x} {3}(..)] "), line.FileName, line.LineNumber, address, symbol->Name);
    }

    void Logger::writeLog(LogType type, const tchar* str, size_t length) {
        criticalSection.enter();
        logOutput->log(type, str, length);
        criticalSection.leave();
    }

    void Logger::init(LogOutput* output) {
        if (logOutput)
            uninit();

#ifdef _DEBUG
        filterLevel = LogType::INFO;
#else
        filterLevel = LogType::ERR0R;
#endif

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

        if (output) {
            logOutput = output;
        } else {
            logOutput = ghnew SystemConsoleLogOutput();
        }
    }

    void Logger::uninit() {
        if (symbol != nullptr) {
            delete[] symbol;
            symbol = nullptr;
            SymCleanup(process);
            process = {};
        }

        delete logOutput;
        logOutput = nullptr;
    }
}