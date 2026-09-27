#pragma once

#include "Common.h"
#include "core/object/Noncopyable.h"
#include "Formatter.h"
#include "LogOutput.h"
#include "LogType.h"
#include "core/collection/Set.h"

#include <cstdint>
#include <mutex>

namespace Ghurund::Core {
    class Logger:public Noncopyable {
    private:
        static HANDLE process;
        static std::mutex mutex;
        static LogTypeEnum filterLevel;

        static LogOutput* logOutput;

        struct LogOnceEntry {
            std::basic_string<tchar> fileLine;
            uint32_t id;

            inline auto operator<=>(const LogOnceEntry& other) const = default;
        };

        static Set<LogOnceEntry> logOnceEntries;

        static std::basic_string<tchar> getStacktraceLine(size_t stacktraceEntryIndex);

    public:
        static void init(std::unique_ptr<LogOutput> output = nullptr);

        static void uninit();

        static inline void setFilter(const LogType& level) {
            filterLevel = level.Value;
        }

        /**
        * Logs error with a stacktrace entry, and throws an exception.
        * 'stacktraceEntryIndex' param lets caller pick which stacktrace entry will be logged with the message.
        * Logger internal calls are always skipped in stacktrace entry calculations.
        **/
        template<typename ExceptionType>
        static void logAndThrow(const tchar* text, size_t stacktraceEntryIndex = 0) {
            String strText = text;
            Logger::log(LogType::ERR0R, text, stacktraceEntryIndex + 1);
            AString astrText = convertText<tchar, char>(strText);
            throw ExceptionType(astrText.Data);
        }

        /**
        * Logs message with log type and a stacktrace entry. If log type level is lower than log filter level, then the log is skipped.
        * 'stacktraceEntryIndex' param lets caller pick which stacktrace entry will be logged with the message.
        * Logger internal calls are always skipped in stacktrace entry calculations.
        **/
        static void log(const LogType& type, const tchar* text, size_t stacktraceEntryIndex = 0);

        /**
        * Logs message with log type and a stacktrace entry, once per logId and stacktraceEntryIndex.
        * If log type level is lower than log filter level, then the log is skipped.
        * 'stacktraceEntryIndex' param lets caller pick which stacktrace entry will be logged with the message.
        * Logger internal calls are always skipped in stacktrace entry calculations.
        **/
        static void logOnce(const LogType& type, const tchar* text, uint32_t logId = 0, size_t stacktraceEntryIndex = 0);

        /**
        * Logs message with log type, once per logId and stacktraceEntryIndex.
        * If log type level is lower than log filter level, then the log is skipped.
        **/
        static inline void print(const LogType& type, const tchar* text) {
            if (((int)type.Value) < (int)filterLevel)
                return;

            std::unique_lock lock(mutex);
            logOutput->log({ type, _T(""), text });
        }
    };
}
