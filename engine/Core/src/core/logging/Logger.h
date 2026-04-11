#pragma once

#include "Common.h"
#include "core/object/Noncopyable.h"
#include "core/threading/CriticalSection.h"
#include "Formatter.h"
#include "LogOutput.h"
#include "LogType.h"
#include "core/collection/Set.h"

#include <cstdint>

namespace Ghurund::Core {
    class Logger:public Noncopyable {
    private:
        static HANDLE process;
        static CriticalSection criticalSection;
        static LogTypeEnum filterLevel;

        static LogOutput* logOutput;

        struct LogOnceEntry {
            std::basic_string<tchar> fileLine;
            uint32_t id;

            inline auto operator<=>(const LogOnceEntry& other) const = default;
        };

        static Set<LogOnceEntry> logOnceEntries;

    public:
        static void init(std::unique_ptr<LogOutput> output = nullptr);

        static void uninit();

        static inline void setFilter(const LogType& level) {
            filterLevel = level.Value;
        }

        static void log(const LogType& type, const tchar* text);

        static void logOnce(const LogType& type, const tchar* text, uint32_t logId = 0);

        static inline void print(const LogType& type, const tchar* text) {
            if (((int)type.Value) < (int)filterLevel)
                return;

            criticalSection.enter();
            logOutput->log({ type, _T(""), text });
            criticalSection.leave();
        }
    };
}
