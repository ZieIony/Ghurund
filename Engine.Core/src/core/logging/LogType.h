#pragma once

#include "core/Enum.h"

namespace Ghurund {
    enum class LogTypeEnum {
        INFO, WARNING, ERR0R
    };

    class LogType : public Enum<LogTypeEnum, LogType> {
    private:
        explicit LogType(LogTypeEnum value, const char* name):Enum<LogTypeEnum, LogType>(value, name) {}

    public:
        static const LogType INFO, WARNING, ERR0R;

        static const EnumValues<LogTypeEnum, LogType> VALUES;
    };

}