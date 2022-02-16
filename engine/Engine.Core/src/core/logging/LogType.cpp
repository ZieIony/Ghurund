#include "ghcpch.h"
#include "LogType.h"

namespace Ghurund::Core {
    const LogType LogType::INFO = LogType(LogTypeEnum::INFO, "INFO", 0xffffffff, 7);
    const LogType LogType::WARNING = LogType(LogTypeEnum::WARNING, "WARNING", 0xffffff7f, 6);
    const LogType LogType::ERR0R = LogType(LogTypeEnum::ERR0R, "ERROR", 0xffff0000, 4);
}