#pragma once

#include "Log.h"
#include "LogOutput.h"
#include "core/string/String.h"

namespace Ghurund::Core {
    class CustomConsoleLogOutput: public LogOutput {
    private:
        String name;
        HANDLE debugOutput;

    public:
        CustomConsoleLogOutput(const String& name);

        ~CustomConsoleLogOutput() {
            FreeConsole();
        }

        virtual void log(const Log& log) override;
    };
}
