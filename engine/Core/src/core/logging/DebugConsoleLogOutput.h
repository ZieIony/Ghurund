#pragma once

#include "Log.h"
#include "LogOutput.h"

namespace Ghurund::Core {
    class DebugConsoleLogOutput: public LogOutput {
    public:
        DebugConsoleLogOutput() {
#ifdef UNICODE
            //_setmode(_fileno(stdout), _O_U16TEXT);
            SetConsoleOutputCP(65001);
#endif
        }

        virtual void log(const Log& log) override;
    };
}
