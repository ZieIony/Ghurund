#pragma once

#include "../Ghurund.h"
#include "Noncopyable.h"
#include "Enum.h"
#include "dbghelp.h"
#include "CriticalSection.h"
#include "collection/String.h"
#include <functional>

namespace Ghurund {
    enum class LogOutput {
        SYSTEM_CONSOLE, CUSTOM_CONSOLE, FILE, CUSTOM_CALLBACK
    };

    enum class LogTypeEnum {
        INFO, WARNING, ERR0R
    };

    class LogType: public Enum<LogTypeEnum, LogType> {
    private:
        explicit LogType(LogTypeEnum value, const tchar* name):Enum<LogTypeEnum, LogType>(value, name) {}

    public:
        static const LogType INFO, WARNING, ERR0R;
    };

    class Logger:public Noncopyable {
    private:
        static HANDLE debugOutput;
        static HANDLE file;
        static LogOutput output;
        static HANDLE process;
        static SYMBOL_INFO* symbol;
        static IMAGEHLP_LINE line;
        static CriticalSection criticalSection;
        static std::function<void(const tchar*)> onLogged;
        static const LogType* filterLevel;

        static address_t getAddress();

        static String getFileLine(address_t address);

        static void logVA(const LogType& type, const String& format, va_list args);
        static void writeLog(const tchar* str, size_t length);

    public:
        static void init(LogOutput output = LogOutput::SYSTEM_CONSOLE, const tchar* name = nullptr, std::function<void(const tchar*)> onLogged = nullptr);

        static void uninit();

        static void setFilter(const LogType& level) {
            filterLevel = &level;
        }

        static void log(const LogType& type, const tchar* format, ...);
        static Status log(const LogType& type, Status status, const tchar* format, ...);
    };

}