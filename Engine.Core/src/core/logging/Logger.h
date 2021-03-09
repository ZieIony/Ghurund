#pragma once

#include "Common.h"
#include "Status.h"
#include "LogType.h"
#include "LogOutput.h"
#include "core/Noncopyable.h"
#include "core/threading/CriticalSection.h"

#include "fmt/core.h"

struct _SYMBOL_INFO;

namespace Ghurund {
    class Logger:public Noncopyable {
    private:
        static HANDLE process;
        static _SYMBOL_INFO* symbol;
        static CriticalSection criticalSection;
        static LogTypeEnum filterLevel;

        static LogOutput* logOutput;

        static address_t getAddress();

        static std::basic_string<tchar> getFileLine(address_t address);

        template<typename... Args>
        static void logVA(LogType type, const tchar* formatStr, Args&& ... args) {
            if (((int)type.Value) < (int)filterLevel)
                return;

            std::basic_string<tchar> fileLine = getFileLine(getAddress());
            std::basic_string<tchar> message = fmt::format(formatStr, args...);

            criticalSection.enter();
            logOutput->log({ type, fileLine.c_str(), message.c_str() });
            criticalSection.leave();
        }

    public:
        static void init(std::unique_ptr<LogOutput> output = nullptr);

        static void uninit();

        static void setFilter(const LogType& level) {
            filterLevel = level.Value;
        }

        template<typename... Args>
        static void log(LogType type, const tchar* format, Args&& ... args) {
            logVA(type, format, args...);
        }

        template<typename... Args>
        static Status log(LogType type, const Status status, const tchar* format, Args&& ... args) {
            logVA(type, format, args...);
            return status;
        }
    };

}