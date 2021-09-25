#pragma once

#include "core/Enum.h"

namespace Ghurund::Core {
    enum class LogTypeEnum {
        INFO, WARNING, ERR0R
    };

    class LogType: public Enum<LogTypeEnum, LogType> {
    private:
        uint32_t color, styleCode;

        LogType(LogTypeEnum value, const char* name, uint32_t color, uint32_t styleCode):Enum<LogTypeEnum, LogType>(value, name), color(color), styleCode(styleCode) {}

    public:
        static const LogType INFO, WARNING, ERR0R;

        static const EnumValues<LogTypeEnum, LogType> VALUES;

        inline uint32_t getColor() const {
            return color;
        }

        __declspec(property(get = getColor)) uint32_t Color;

        inline uint32_t getStyleCode() const {
            return styleCode;
        }

        __declspec(property(get = getStyleCode)) uint32_t StyleCode;
    };

}