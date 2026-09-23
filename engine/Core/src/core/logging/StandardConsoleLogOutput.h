#pragma once

#include "Log.h"
#include "LogOutput.h"
#include "core/string/String.h"

namespace Ghurund::Core {
    class StandardConsoleLogOutput: public LogOutput {
    private:
        String name;
        HANDLE debugOutput;

    public:
        StandardConsoleLogOutput() {
            debugOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        }

        virtual void log(const Log& log) override;
    };
}
