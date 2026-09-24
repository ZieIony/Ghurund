#pragma once

#include "core/collection/List.h"
#include "core/collection/Queue.h"

#include <condition_variable>
#include <coroutine>
#include <mutex>
#include <thread>

namespace Ghurund::Core {
    class CoroutineThreadPool {
    private:
        struct Awaiter {
            CoroutineThreadPool* threadPool;

            constexpr bool await_ready() const noexcept { return false; }
            constexpr void await_resume() const noexcept {}
            void await_suspend(std::coroutine_handle<> coro) const noexcept {
                threadPool->enqueueTask(coro);
            }
        };

        List<std::thread> threads;

        std::mutex mutex;
        std::condition_variable conditionVariable;
        Queue<std::coroutine_handle<>> coroutines;

        bool stopThreads = false;

        void threadLoop();

        void enqueueTask(std::coroutine_handle<> coro) noexcept {
            std::unique_lock<std::mutex> lock(mutex);
            coroutines.add(coro);
            conditionVariable.notify_one();
        }

		void shutdown();

	public:
        explicit CoroutineThreadPool(size_t threadCount);

        ~CoroutineThreadPool() {
            shutdown();
        }

        Awaiter schedule() {
            return { this };
        }
    };
}
