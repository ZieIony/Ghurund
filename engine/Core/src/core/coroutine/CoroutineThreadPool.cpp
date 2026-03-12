#include "ghcpch.h"
#include "CoroutineThreadPool.h"

namespace Ghurund::Core {
    void CoroutineThreadPool::threadLoop() {
        while (!stopThreads) {
            std::unique_lock<std::mutex> lock(mutex);
            conditionVariable.wait(lock);

            if (stopThreads)
                break;

            auto coro = coroutines.front();
            coroutines.remove();
            coro.resume();
        }
    }
    
    void CoroutineThreadPool::shutdown() {
        {
            std::unique_lock<std::mutex> lock(mutex);
            stopThreads = true;
        }
        conditionVariable.notify_all();

        while (threads.Size > 0) {
            std::thread& thread = threads[threads.Size - 1];
            if (thread.joinable()) {
                thread.join();
            }
            threads.removeAt(threads.Size - 1);
        }
    }
    
    CoroutineThreadPool::CoroutineThreadPool(size_t threadCount) {
        for (size_t i = 0; i < threadCount; ++i) {
            std::thread thread([this]() {
                threadLoop();
            });
            threads.add(std::move(thread));
        }
    }
}
