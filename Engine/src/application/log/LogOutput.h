#pragma once

#include "Status.h"
#include "core/Enum.h"
#include "core/string/String.h"
#include "LogType.h"

#include <functional>

namespace Ghurund {
    __interface LogOutput {
        virtual void log(const tchar* str, size_t length) = 0;
    };

    class CustomConsoleLogOutput : public LogOutput {
    private:
        String name;
        HANDLE debugOutput;

    public:
        CustomConsoleLogOutput(const String& name): name(name) {
            AllocConsole();
            SetConsoleTitle(name);
            debugOutput = GetStdHandle(STD_OUTPUT_HANDLE);
            COORD co = { 80,25 };
            SetConsoleScreenBufferSize(debugOutput, co);
        }

        ~CustomConsoleLogOutput() {
            FreeConsole();
        }

        void log(const tchar* str, size_t length) {
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

        void log(const tchar* str, size_t length) {
            OutputDebugString(str);
        }
    };

    class FileLogOutput : public LogOutput {
    private:
        String name;
        HANDLE file;

    public:
        FileLogOutput(const String& name): name(name) {
            file = CreateFile(name, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        }

        ~FileLogOutput() {
            CloseHandle(file);
        }

        void log(const tchar* str, size_t length) {
            unsigned long bytes;
            WriteFile(file, str, (DWORD)(length * sizeof(tchar)), &bytes, nullptr);
        }
    };

    class CallbackLogOutput : public LogOutput {
    private:
        std::function<void(const tchar*)> onLogged;

    public:
        CallbackLogOutput(std::function<void(const tchar*)> onLogged): onLogged(onLogged) {
        }

        void log(const tchar* str, size_t length) {
            onLogged(str);
        }
    };
}