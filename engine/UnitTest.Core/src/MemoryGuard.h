#pragma once

#include "CppUnitTest.h"

#include <crtdbg.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

class MemoryGuard {
private:
    _CrtMemState state;

public:
    MemoryGuard() {
        _CrtMemCheckpoint(&state);
    }

    ~MemoryGuard() {
        _CrtMemState state2;
        _CrtMemCheckpoint(&state2);
        _CrtMemState diff;
        Assert::AreEqual(0, _CrtMemDifference(&diff, &state, &state2), L"memory leaks detected");
        Assert::AreEqual(1, _CrtCheckMemory(), L"memory corruption detected");
    }
};
