#pragma once

#include "../Ghurund.h"
#include "Noncopyable.h"
#include "dbghelp.h"
#include "CriticalSection.h"
#include "collection/String.h"
#include <functional>

namespace Ghurund {
    enum class LogOutput {
        SYSTEM_CONSOLE, CUSTOM_CONSOLE, FILE, CUSTOM_CALLBACK
    };

    class LogType {
    private:
        const tchar* name;

        LogType() = default;

    public:
        static const LogType& INFO, & WARNING, & ERR0R;

        explicit LogType(const tchar* name) {
            this->name = name;
        }

        const tchar* getName() const {
            return name;
        }

        __declspec(property(get = getName)) const tchar* Name;

        bool operator==(const LogType& type) const {
            return this == &type;
        }

        bool operator==(const LogType& type) {
            return this == &type;
        }
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

        static address_t getAddress();

        static String getFileLine(address_t address);

        static void logVA(const LogType& type, const String& format, va_list args);
        static void writeLog(const tchar* str, size_t length);

    public:
        static void init(LogOutput output = LogOutput::SYSTEM_CONSOLE, const tchar* name = nullptr, std::function<void(const tchar*)> onLogged = nullptr);

        static void uninit();

        static void log(const LogType& type, const tchar* format, ...);
        static Status log(const LogType& type, Status status, const tchar* format, ...);
    };

}