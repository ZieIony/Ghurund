#include "ghcpch.h"
#include "Formatter.h"
#include "Logger.h"

#include "Common.h"

#include <io.h>
#include <fcntl.h>
#include <process.h>
#include <dbghelp.h>

namespace Ghurund {
    using namespace std;

    HANDLE Logger::process;
    CriticalSection Logger::criticalSection;
    LogTypeEnum Logger::filterLevel = LogType::INFO.Value;
    LogOutput* Logger::logOutput = nullptr;

    void Logger::init(std::unique_ptr<LogOutput> output) {
        if (logOutput)
            uninit();

#ifdef _DEBUG
        filterLevel = LogType::INFO.Value;
#else
        filterLevel = LogType::ERR0R.Value;
#endif

        process = GetCurrentProcess();
        SymInitialize(process, NULL, TRUE);

        if (output) {
            logOutput = output.release();
        } else {
            logOutput = ghnew SystemConsoleLogOutput();
        }
    }

    void Logger::uninit() {
        SymCleanup(process);

        delete logOutput;
        logOutput = nullptr;
    }
}