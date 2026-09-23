#pragma once

#include "Log.h"
#include "LogOutput.h"

#include <functional>

namespace Ghurund::Core {
    class CallbackLogOutput: public LogOutput {
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
