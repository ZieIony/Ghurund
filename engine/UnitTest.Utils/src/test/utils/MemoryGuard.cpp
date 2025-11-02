#include "MemoryGuard.h"

#include <format>

namespace UnitTest::Utils {
    int reportHook(int reportType, char* message, int* returnValue) {
        Logger::WriteMessage(message);
        return 0;
    }

    MemoryGuard::MemoryGuard() {
#ifdef _DEBUG
        _CrtMemCheckpoint(&state);
        _CrtSetReportHook(&reportHook);
#endif
    }

    MemoryGuard::~MemoryGuard() {
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
}
