#pragma once

#include "Log.h"
#include "Status.h"
#include "core/Enum.h"
#include "core/string/String.h"

#include <functional>

namespace Ghurund::Core {
    class LogOutput {
    public:
        virtual ~LogOutput() = 0 {}

        virtual void log(const Log& log) = 0;
    };

    class CustomConsoleLogOutput: public LogOutput {
    private:
        String name;
        HANDLE debugOutput;

    public:
        CustomConsoleLogOutput(const String& name): name(name) {
            AllocConsole();
            SetConsoleTitle(name.Data);
            debugOutput = GetStdHandle(STD_OUTPUT_HANDLE);
            COORD co = { 80,25 };
            SetConsoleScreenBufferSize(debugOutput, co);
        }

        ~CustomConsoleLogOutput() {
            FreeConsole();
        }

        virtual void log(const Log& log) override {
            SetConsoleTextAttribute(debugOutput, log.type.StyleCode);
            if (!log.fileLine.Empty) {
                WriteConsole(debugOutput, log.fileLine.Data, (DWORD)log.fileLine.Length, nullptr, nullptr);
                WriteConsole(debugOutput, ": ", 2, nullptr, nullptr);
            }
            WriteConsole(debugOutput, log.message.Data, (DWORD)log.message.Length, nullptr, nullptr);
            SetConsoleTextAttribute(debugOutput, LogType::INFO.StyleCode);
        }
    };

    class StandardConsoleLogOutput: public LogOutput {
    private:
        String name;
        HANDLE debugOutput;

    public:
        StandardConsoleLogOutput() {
            debugOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        }

        virtual void log(const Log& log) override {
            SetConsoleTextAttribute(debugOutput, log.type.StyleCode);
            if (!log.fileLine.Empty) {
                WriteConsole(debugOutput, log.fileLine.Data, (DWORD)log.fileLine.Length, nullptr, nullptr);
                WriteConsole(debugOutput, ": ", 2, nullptr, nullptr);
            }
            WriteConsole(debugOutput, log.message.Data, (DWORD)log.message.Length, nullptr, nullptr);
            SetConsoleTextAttribute(debugOutput, LogType::INFO.StyleCode);
        }
    };

    class DebugConsoleLogOutput : public LogOutput {
    public:
        DebugConsoleLogOutput() {
#ifdef UNICODE
            //_setmode(_fileno(stdout), _O_U16TEXT);
            SetConsoleOutputCP(65001);
#endif
        }

        virtual void log(const Log& log) override {
            if (!log.fileLine.Empty) {
                OutputDebugString(log.fileLine.Data);
                OutputDebugString(_T(": "));
            }
            OutputDebugString(log.message.Data);
        }
    };

    class FileLogOutput : public LogOutput {
    private:
        String name;
        HANDLE file;

    public:
        FileLogOutput(const String& name): name(name) {
            file = CreateFile(name.Data, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        }

        ~FileLogOutput() {
            CloseHandle(file);
        }

        virtual void log(const Log& log) override {
            unsigned long bytes;
            if (!log.fileLine.Empty) {
                WriteFile(file, log.fileLine.Data, (DWORD)(log.fileLine.Length * sizeof(tchar)), &bytes, nullptr);
                WriteFile(file, L": ", (DWORD)(2 * sizeof(tchar)), &bytes, nullptr);
            }
            WriteFile(file, log.message.Data, (DWORD)(log.message.Length * sizeof(tchar)), &bytes, nullptr);
        }
    };

    class CallbackLogOutput : public LogOutput {
    private:
        std::function<void(const Log&)> onLogged;

    public:
        CallbackLogOutput(std::function<void(const Log&)> onLogged): onLogged(onLogged) {
        }

        virtual void log(const Log& log) override {
            onLogged(log);
        }
    };
}