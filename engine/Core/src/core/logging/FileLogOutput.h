#pragma once

#include "Log.h"
#include "LogOutput.h"
#include "core/string/String.h"

namespace Ghurund::Core {
    class FileLogOutput: public LogOutput {
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

        virtual void log(const Log& log) override;
    };
}
