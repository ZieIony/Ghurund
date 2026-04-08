#include "utcpch.h"
#include "CppUnitTest.h"

#include <test/utils/MemoryGuard.h>
#include <core/coroutine/CoroutineThreadPool.h>
#include <core/coroutine/CoroutineTask.h>
#include <core/coroutine/CoroutineScheduler.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace std;
    using namespace Ghurund::Core;

    TEST_CLASS(CoroutineTaskTest) {
public:

    TEST_METHOD(CoroutineTask_continuation) {
        MemoryGuard guard;
        {
            auto mainId = std::this_thread::get_id();
            CoroutineThreadPool threadPool(1);
            Timer timer;
            CoroutineScheduler scheduler(threadPool, timer);
            // let the thread pool start
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            std::thread::id backgroundId = mainId;

            auto inner = [&] -> CoroutineTask<void> {
                co_await scheduler.mainThread();
            };

            auto task = [&] -> CoroutineTask<void> {
                co_await scheduler.backgroundThread();
                auto id = std::this_thread::get_id();
                co_await inner();
                backgroundId = id;
            }();
            task.resume();

            // let the coroutines get thread id
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            scheduler.update();
            scheduler.update();
            auto currentId = std::this_thread::get_id();
            Assert::IsTrue(backgroundId != mainId);
            Assert::IsTrue(currentId == mainId);
        }
    }

    TEST_METHOD(CoroutineTask_return) {
        MemoryGuard guard;
        {
            uint32_t result;
            CoroutineThreadPool threadPool(1);
            Timer timer;
            CoroutineScheduler scheduler(threadPool, timer);
            // let the thread pool start
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            auto inner = [&] -> CoroutineTask<uint32_t> {
                co_await scheduler.mainThread();
                co_return (uint32_t)5;
            };

            auto task = [&] -> CoroutineTask<void> {
                co_await scheduler.backgroundThread();
                result = co_await inner();
            }();
            task.resume();

            // let the coroutines get thread id
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            scheduler.update();
            scheduler.update();
            Assert::IsTrue(5 == result);
        }
    }
    };
}
