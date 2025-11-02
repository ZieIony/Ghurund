#pragma once

#include "CppUnitTest.h"

#ifdef _DEBUG
#include <crtdbg.h>
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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