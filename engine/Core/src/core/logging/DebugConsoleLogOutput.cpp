#include "ghcpch.h"
#include "DebugConsoleLogOutput.h"

namespace Ghurund::Core {
    void DebugConsoleLogOutput::log(const Log& log) {
        if (!log.fileLine.IsEmpty) {
            OutputDebugString(log.fileLine.Data);
            OutputDebugString(_T(": "));
        }
        OutputDebugString(log.message.Data);
    }
}
