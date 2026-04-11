#include "utcpch.h"
#include "CppUnitTest.h"

#include <test/utils/MemoryGuard.h>
#include "core/coroutine/CoroutineThreadPool.h"
#include "core/coroutine/CoroutineTask.h"
#include "core/coroutine/CoroutineScheduler.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace std;
    using namespace Ghurund::Core;

    TEST_CLASS(CoroutineThreadPoolTest) {
public:

    TEST_METHOD(CoroutineThreadPool_init_shutdown) {
        MemoryGuard guard;
        {
            CoroutineThreadPool threadPool(4);
        }
    }

    TEST_METHOD(CoroutineThreadPool_noThreads) {
        MemoryGuard guard;
        {
            CoroutineThreadPool threadPool(0);
        }
    }

    TEST_METHOD(CoroutineThreadPool_schedule) {
        MemoryGuard guard;
        {
            CoroutineThreadPool threadPool(4);
            Timer timer;
            CoroutineScheduler scheduler(threadPool, timer);
            // let the thread pool start
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            List<std::thread::id> ids;
            auto task = [&] -> CoroutineTask<void> {
                co_await threadPool.schedule();
                auto id = std::this_thread::get_id();
                co_await scheduler.nextUpdate();
                ids.add(id);
            };
            scheduler.launch(task());
            scheduler.launch(task());
            // let the coroutines get thread id
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            scheduler.update();
            Assert::IsTrue(ids[0] != ids[1]);
        }
    }
    };
}
