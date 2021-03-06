#pragma once

#include "Status.h"
#include "core/Enum.h"
#include "core/string/String.h"

namespace Ghurund {
    __interface LogOutput {
        virtual void log(LogType type, const tchar* str, size_t length) = 0;
    };

    class CustomConsoleLogOutput : public LogOutput {
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

        virtual void log(LogType type, const tchar* str, size_t length) override {
            WriteConsole(debugOutput, str, (DWORD)length, nullptr, nullptr);
        }
    };

    class SystemConsoleLogOutput : public LogOutput {
    public:
        SystemConsoleLogOutput() {
#ifdef UNICODE
            //_setmode(_fileno(stdout), _O_U16TEXT);
            SetConsoleOutputCP(65001);
#endif
        }

        virtual void log(LogType type, const tchar* str, size_t length) override {
            OutputDebugString(str);
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

        virtual void log(LogType type, const tchar* str, size_t length) override {
            unsigned long bytes;
            WriteFile(file, str, (DWORD)(length * sizeof(tchar)), &bytes, nullptr);
        }
    };

    class CallbackLogOutput : public LogOutput {
    private:
        std::function<void(LogType, const tchar*)> onLogged;

    public:
        CallbackLogOutput(std::function<void(LogType, const tchar*)> onLogged): onLogged(onLogged) {
        }

        virtual void log(LogType type, const tchar* str, size_t length) override {
            onLogged(type, str);
        }
    };
}