#pragma once

#include "Common.h"
#include "Status.h"
#include "core/Noncopyable.h"
#include "core/threading/CriticalSection.h"

#include "fmt/core.h"

struct _SYMBOL_INFO;

namespace Ghurund {
    __interface LogOutput;

    enum class LogType {
        INFO, WARNING, ERR0R
    };

    class Logger:public Noncopyable {
    private:
        static HANDLE process;
        static _SYMBOL_INFO* symbol;
        static CriticalSection criticalSection;
        static LogType filterLevel;

        static LogOutput* logOutput;

        static address_t getAddress();

        static std::basic_string<tchar> getFileLine(address_t address);

        template<typename... Args>
        static void logVA(LogType type, const tchar* formatStr, Args&& ... args) {
            std::basic_string<tchar> fileLine = getFileLine(getAddress());

            std::basic_string<tchar> message = fmt::format(formatStr, args...);
            std::basic_string<tchar> log = fileLine + message;

            writeLog(type, log.c_str(), log.size());
        }

        static void writeLog(LogType type, const tchar* str, size_t length);

    public:
        static void init(LogOutput* output = nullptr);

        static void uninit();

        static void setFilter(const LogType& level) {
            filterLevel = level;
        }

        template<typename... Args>
        static void log(LogType type, const tchar* format, Args&& ... args) {
            if (((int)type) < (int)filterLevel)
                return;

            logVA(type, format, args...);
        }

        template<typename... Args>
        static Status log(LogType type, const Status status, const tchar* format, Args&& ... args) {
            if (((int)type) < (int)filterLevel)
                return status;

            logVA(type, format, args...);

            return status;
        }
    };

}