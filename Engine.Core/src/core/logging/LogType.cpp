#include "LogType.h"

namespace Ghurund {
    const LogType LogType::INFO = LogType(LogTypeEnum::INFO, "INFO");
    const LogType LogType::WARNING = LogType(LogTypeEnum::WARNING, "WARNING");
    const LogType LogType::ERR0R = LogType(LogTypeEnum::ERR0R, "ERROR");

    const EnumValues<LogTypeEnum, LogType> LogType::VALUES = {
        &LogType::INFO,
        &LogType::WARNING,
        &LogType::ERR0R
    };
}