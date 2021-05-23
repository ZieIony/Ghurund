#include "pch.h"
#include "CppUnitTest.h"

#include "core/Object.h"
#include "core/threading/WorkerThread.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund;

    TEST_CLASS(WorkerThreadTest) {
public:

    TEST_METHOD(WorkerThread_getTasks) {
        {
            WorkerThread thread;
            auto tasks = thread.Tasks;
            Assert::AreEqual(true, tasks.Empty);
        }
        _____________________checkMemory();
    }

    TEST_METHOD(WorkerThread_finish) {
        {
            WorkerThread thread;
            thread.finish();
            Assert::AreEqual(false, thread.Running);
            Assert::AreEqual(INVALID_HANDLE_VALUE, thread.Handle);
        }
        _____________________checkMemory();
    }
    };
}
