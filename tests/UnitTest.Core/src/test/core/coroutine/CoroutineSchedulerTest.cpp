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

    TEST_CLASS(CoroutineSchedulerTest) {
public:

    TEST_METHOD(CoroutineScheduler_background_main) {
        MemoryGuard guard;
        {
            auto mainId = std::this_thread::get_id();
            CoroutineThreadPool threadPool(1);
            // let the thread pool start
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            Timer timer;
            CoroutineScheduler scheduler(threadPool, timer);
            std::thread::id backgroundId, emptyId;

            scheduler.launch([&] -> CoroutineTask<void> {
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
            // let the thread pool start
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            Timer timer;
            CoroutineScheduler scheduler(threadPool, timer);
            std::thread::id delayId, emptyId;

            scheduler.launch([&] -> CoroutineTask<void> {
                co_await scheduler.delay(0.01f);
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
            // let the thread pool start
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            Timer timer;
            CoroutineScheduler scheduler(threadPool, timer);
            timer.tick();
            std::thread::id delayId, emptyId;

            scheduler.launch([&] -> CoroutineTask<void> {
                co_await scheduler.delayedUpdate(0.01f, false);
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

    TEST_METHOD(CoroutineScheduler_delayedUpdate_timeScale) {
        MemoryGuard guard;
        {
            CoroutineThreadPool threadPool(1);
            // let the thread pool start
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            Timer timer;
            CoroutineScheduler scheduler(threadPool, timer);
            timer.tick();

            auto task = [&] -> CoroutineTask<void> {
                co_await scheduler.delayedUpdate(0.01f, true);
            }();
            scheduler.launch(task);

            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            timer.TimeScale = 0.0f;
            timer.tick();
            scheduler.update();
            Assert::IsFalse(task.IsDone);

            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            timer.TimeScale = 1.0f;
            timer.tick();
            scheduler.update();
            Assert::IsTrue(task.IsDone);
        }
    }

    TEST_METHOD(CoroutineScheduler_nextUpdate) {
        MemoryGuard guard;
        {
            CoroutineThreadPool threadPool(1);
            // let the thread pool start
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            Timer timer;
            CoroutineScheduler scheduler(threadPool, timer);
            timer.tick();
            timer.TimeScale = 0.0f;

            auto task = [&] -> CoroutineTask<void> {
                co_await scheduler.nextUpdate();
            }();
            scheduler.launch(task);

            scheduler.fixedUpdate();
            Assert::IsFalse(task.IsDone);

            scheduler.update();
            Assert::IsTrue(task.IsDone);
        }
    }

    TEST_METHOD(CoroutineScheduler_nextFixedUpdate) {
        MemoryGuard guard;
        {
            CoroutineThreadPool threadPool(1);
            // let the thread pool start
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            Timer timer;
            CoroutineScheduler scheduler(threadPool, timer);
            timer.tick();
            timer.TimeScale = 0.0f;

            auto task = [&] -> CoroutineTask<void> {
                co_await scheduler.nextFixedUpdate();
            }();
            scheduler.launch(task);

            scheduler.update();
            Assert::IsFalse(task.IsDone);

            scheduler.fixedUpdate();
            Assert::IsTrue(task.IsDone);
        }
    }
    };
}
