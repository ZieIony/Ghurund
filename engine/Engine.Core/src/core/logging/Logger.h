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

namespace Ghurund::Core {
    class Logger:public Noncopyable {
    private:
        static HANDLE process;
        static CriticalSection criticalSection;
        static LogTypeEnum filterLevel;

        static LogOutput* logOutput;

    public:
        static void init(std::unique_ptr<LogOutput> output = nullptr);

        static void uninit();

        static inline void setFilter(const LogType& level) {
            filterLevel = level.Value;
        }

        static void log(const LogType& type, const tchar* text);

        static inline Status log(const LogType& type, const Status status, const tchar* text) {
            log(type, text);
            return status;
        }

        static inline void print(const LogType& type, const tchar* text) {
            if (((int)type.Value) < (int)filterLevel)
                return;

            criticalSection.enter();
            logOutput->log({ type, _T(""), text });
            criticalSection.leave();
        }
    };
}