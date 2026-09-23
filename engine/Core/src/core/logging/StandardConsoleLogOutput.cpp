#include "ghcpch.h"
#include "StandardConsoleLogOutput.h"

namespace Ghurund::Core {
    void StandardConsoleLogOutput::log(const Log& log) {
        SetConsoleTextAttribute(debugOutput, log.type.StyleCode);
        if (!log.fileLine.IsEmpty) {
            WriteConsole(debugOutput, log.fileLine.Data, (DWORD)log.fileLine.Length, nullptr, nullptr);
            WriteConsole(debugOutput, ": ", 2, nullptr, nullptr);
        }
        WriteConsole(debugOutput, log.message.Data, (DWORD)log.message.Length, nullptr, nullptr);
        SetConsoleTextAttribute(debugOutput, LogType::INFO.StyleCode);
    }
}
