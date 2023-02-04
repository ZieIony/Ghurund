#pragma once

#include "CppUnitTest.h"

#ifdef _DEBUG
#include <crtdbg.h>
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest::Utils {
    class MemoryGuard {
    private:
#ifdef _DEBUG
        _CrtMemState state;
#endif

    public:
        MemoryGuard() {
#ifdef _DEBUG
            _CrtMemCheckpoint(&state);
#endif
        }

        ~MemoryGuard() {
#ifdef _DEBUG
            _CrtMemState state2;
            _CrtMemCheckpoint(&state2);
            auto memCheck = _CrtCheckMemory();
            Assert::AreEqual(1, memCheck, L"memory corruption detected");
            _CrtMemState diff;
            auto memDiff = _CrtMemDifference(&diff, &state, &state2);
            if (memDiff != 0)
                _CrtMemDumpAllObjectsSince(&state);
            Assert::AreEqual(0, memDiff, L"memory leaks detected");
#endif
        }
    };
}