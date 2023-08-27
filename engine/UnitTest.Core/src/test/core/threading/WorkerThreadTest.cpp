#include "pch.h"
#include "CppUnitTest.h"

#include "core/Object.h"
#include "core/threading/WorkerThread.h"
#include "test/MemoryGuard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;

    TEST_CLASS(WorkerThreadTest) {
public:

    TEST_METHOD(WorkerThread_getTasks) {
        MemoryGuard guard;
        {
            WorkerThread thread;
            auto tasks = thread.Tasks;
            Assert::AreEqual(true, tasks.Empty);
        }
    }

    TEST_METHOD(WorkerThread_finish) {
        MemoryGuard guard;
        {
            WorkerThread thread;
            thread.start();
            thread.finish();
            Assert::AreEqual(false, thread.Running);
            Assert::AreEqual(INVALID_HANDLE_VALUE, thread.Handle);
        }
    }
    };
}
