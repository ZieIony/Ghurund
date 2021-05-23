#pragma once

#include "CriticalSection.h"

#include <Windows.h>

namespace Ghurund {
    class ConditionVariable {
    private:
        CONDITION_VARIABLE variable;

    public:
        ConditionVariable() {
            InitializeConditionVariable(&variable);
        }

        ConditionVariable(ConditionVariable& other) = delete;

        inline void wait(CriticalSection& section) {
            SleepConditionVariableCS(&variable, &section, INFINITE);
        }

        inline void notify() {
            WakeConditionVariable(&variable);
        }

        inline void notifyAll() {
            WakeAllConditionVariable(&variable);
        }
    };
}