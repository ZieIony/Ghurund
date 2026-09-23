#include "ghcpch.h"
#include "FileLogOutput.h"

namespace Ghurund::Core {
    void FileLogOutput::log(const Log& log) {
        unsigned long bytes;
        if (!log.fileLine.IsEmpty) {
            WriteFile(file, log.fileLine.Data, (DWORD)(log.fileLine.Length * sizeof(tchar)), &bytes, nullptr);
            WriteFile(file, L": ", (DWORD)(2 * sizeof(tchar)), &bytes, nullptr);
        }
        WriteFile(file, log.message.Data, (DWORD)(log.message.Length * sizeof(tchar)), &bytes, nullptr);
    }
}
