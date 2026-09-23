#include "ghcpch.h"
#include "CustomConsoleLogOutput.h"

namespace Ghurund::Core {
    CustomConsoleLogOutput::CustomConsoleLogOutput(const String& name): name(name) {
        AllocConsole();
        SetConsoleTitle(name.Data);
        debugOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD co = { 80,25 };
        SetConsoleScreenBufferSize(debugOutput, co);
    }

    void CustomConsoleLogOutput::log(const Log& log) {
        SetConsoleTextAttribute(debugOutput, log.type.StyleCode);
        if (!log.fileLine.IsEmpty) {
            WriteConsole(debugOutput, log.fileLine.Data, (DWORD)log.fileLine.Length, nullptr, nullptr);
            WriteConsole(debugOutput, ": ", 2, nullptr, nullptr);
        }
        WriteConsole(debugOutput, log.message.Data, (DWORD)log.message.Length, nullptr, nullptr);
        SetConsoleTextAttribute(debugOutput, LogType::INFO.StyleCode);
    }
}
