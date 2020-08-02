#include "LogType.h"

namespace Ghurund {
    const LogType LogType::INFO = LogType(LogTypeEnum::INFO, _T("INFO"));
    const LogType LogType::WARNING = LogType(LogTypeEnum::WARNING, _T("WARNING"));
    const LogType LogType::ERR0R = LogType(LogTypeEnum::ERR0R, _T("ERROR"));

    const EnumValues<LogTypeEnum, LogType> LogType::VALUES = {
        &LogType::INFO,
        &LogType::WARNING,
        &LogType::ERR0R
    };
}