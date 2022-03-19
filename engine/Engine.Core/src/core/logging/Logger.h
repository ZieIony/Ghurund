#pragma once

#include "Common.h"
#include "Formatter.h"
#include "Status.h"
#include "LogType.h"
#include "LogOutput.h"
#include "core/Noncopyable.h"
#include "core/StackTrace.h"
#include "core/threading/CriticalSection.h"
#include "core/Object.h"

#include <format>

namespace Ghurund::Core {
    class Logger:public Noncopyable {
    private:
        static HANDLE process;
        static CriticalSection criticalSection;
        static LogTypeEnum filterLevel;

        static LogOutput* logOutput;

        template<typename... Args>
        static void logVA(const LogType& type, const tchar* format, Args&& ... args) {
            /*if (((int)type.Value) < (int)filterLevel)
                return;

            StackTrace stacktrace(GetCurrentProcess());
            StackTrace::Entry entry = stacktrace[2];

            std::basic_string<tchar> fileLine = std::format(_T("{0}({1:d}): [{2:#x} {3}(..)]"), entry.fileName, entry.fileLine, entry.address, entry.name);
            std::basic_string<tchar> message = std::format(format, args...);

            criticalSection.enter();
            logOutput->log({ type, fileLine.c_str(), message.c_str() });
            criticalSection.leave();*/
        }

    public:
        static void init(std::unique_ptr<LogOutput> output = nullptr);

        static void uninit();

        static inline void setFilter(const LogType& level) {
            filterLevel = level.Value;
        }

        template<typename... Args>
        static inline void log(const LogType& type, const tchar* format, Args&& ... args) {
            logVA(type, format, args...);
        }

        template<typename... Args>
        static inline Status log(const LogType& type, const Status status, const tchar* format, Args&& ... args) {
            logVA(type, format, args...);
            return status;
        }

        template<typename... Args>
        static inline void print(const LogType& type, const tchar* format, Args&& ... args) {
            /*if (((int)type.Value) < (int)filterLevel)
                return;

            std::basic_string<tchar> message = std::format(format, args...);
            criticalSection.enter();
            logOutput->log({ type, _T(""), message.c_str() });
            criticalSection.leave();*/
        }
    };
}