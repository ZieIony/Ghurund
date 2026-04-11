#include "ghcpch.h"
#include "Logger.h"

#include "Common.h"
#include "Formatter.h"
#include "core/StackTrace.h"

#include <dbghelp.h>

namespace Ghurund::Core {
    using namespace std;

    HANDLE Logger::process;
    CriticalSection Logger::criticalSection;
    LogTypeEnum Logger::filterLevel = LogType::INFO.Value;
    LogOutput* Logger::logOutput = nullptr;
    Set<Logger::LogOnceEntry> Logger::logOnceEntries;

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
            logOutput = ghnew DebugConsoleLogOutput();
        }
    }

    void Logger::uninit() {
        SymCleanup(process);

        delete logOutput;
        logOutput = nullptr;
    }
    
    void Logger::log(const LogType& type, const tchar* text) {
        if (!logOutput || ((int)type.Value) < (int)filterLevel)
            return;

        StackTrace stacktrace(GetCurrentProcess());
        StackTraceEntry entry = stacktrace[1];

        std::basic_string<tchar> fileLine = std::format(_T("{0}({1:d}): [{2:#x} {3}(..)]"), entry.fileName, entry.fileLine, entry.address, entry.name);

        criticalSection.enter();
        logOutput->log({ type, fileLine.c_str(), text });
        criticalSection.leave();
    }

    void Logger::logOnce(const LogType& type, const tchar* text, uint32_t logId) {
        if (!logOutput || ((int)type.Value) < (int)filterLevel)
            return;

        StackTrace stacktrace(GetCurrentProcess());
        StackTraceEntry entry = stacktrace[1];

        std::basic_string<tchar> fileLine = std::format(_T("{0}({1:d}): [{2:#x} {3}(..)]"), entry.fileName, entry.fileLine, entry.address, entry.name);

        LogOnceEntry logOnceEntry = { fileLine, logId };
        if (logOnceEntries.contains(logOnceEntry))
            return;

        logOnceEntries.put(logOnceEntry);

        criticalSection.enter();
        logOutput->log({ type, fileLine.c_str(), text });
        criticalSection.leave();
    }
}
