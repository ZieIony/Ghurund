#pragma once

#ifdef _DEBUG
#include <crtdbg.h>
#endif

namespace UnitTest::Utils {
    int reportHook(int reportType, char* message, int* returnValue);

    class MemoryGuard {
    private:
#ifdef _DEBUG
        _CrtMemState state;
#endif

    public:
        MemoryGuard();

        ~MemoryGuard();
    };
}