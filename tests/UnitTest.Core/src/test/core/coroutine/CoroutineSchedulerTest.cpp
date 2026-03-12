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

    TEST_CLASS(CoroutineSchedulerTest) {
public:

    TEST_METHOD(CoroutineScheduler_background_main) {
        MemoryGuard guard;
        {
            auto mainId = std::this_thread::get_id();
            CoroutineThreadPool threadPool(1);
            Timer timer;
            CoroutineScheduler scheduler(threadPool, timer);
            // let the thread pool start
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            std::thread::id backgroundId, emptyId;
            scheduler.launch([&] -> CoroutineTask {
                co_await scheduler.backgroundThread();
                auto id = std::this_thread::get_id();
                co_await scheduler.mainThread();
                backgroundId = id;
            }());
            // let the coroutines get thread id
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            scheduler.update();
            auto currentId = std::this_thread::get_id();
            Assert::IsTrue(backgroundId != emptyId);
            Assert::IsTrue(backgroundId != mainId);
            Assert::IsTrue(currentId == mainId);
        }
    }

    TEST_METHOD(CoroutineScheduler_delay_main) {
        MemoryGuard guard;
        {
            auto mainId = std::this_thread::get_id();
            CoroutineThreadPool threadPool(1);
            Timer timer;
            CoroutineScheduler scheduler(threadPool, timer);
            // let the thread pool start
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            std::thread::id delayId, emptyId;
            scheduler.launch([&] -> CoroutineTask {
                co_await scheduler.delay(10);
                auto id = std::this_thread::get_id();
                co_await scheduler.mainThread();
                delayId = id;
            }());
            // let the coroutines get thread id
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            scheduler.update();
            auto currentId = std::this_thread::get_id();
            Assert::IsTrue(delayId != emptyId);
            Assert::IsTrue(delayId != mainId);
            Assert::IsTrue(currentId == mainId);
        }
    }

    TEST_METHOD(CoroutineScheduler_delayedUpdate_main) {
        MemoryGuard guard;
        {
            auto mainId = std::this_thread::get_id();
            CoroutineThreadPool threadPool(1);
            Timer timer;
            CoroutineScheduler scheduler(threadPool, timer);
            timer.tick();
            // let the thread pool start
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            std::thread::id delayId, emptyId;
            scheduler.launch([&] -> CoroutineTask {
                co_await scheduler.delayedUpdate(10);
                delayId = std::this_thread::get_id();
            }());
            // let the coroutines get thread id
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            timer.tick();
            scheduler.update();
            Assert::IsTrue(delayId != emptyId);
            Assert::IsTrue(delayId == mainId);
        }
    }
    };
}
