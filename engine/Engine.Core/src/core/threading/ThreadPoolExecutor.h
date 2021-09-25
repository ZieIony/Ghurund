#pragma once

#include "Task.h"
#include "WorkerThread.h"
#include "core/SharedPointer.h"
#include "core/SystemInfo.h"
#include "core/collection/List.h"
#include "core/collection/Map.h"
#include "core/logging/Logger.h"

#include <format>

namespace Ghurund::Core {
    class ThreadPoolExecutor {
    private:
        struct TaskExecution {
            SharedPointer<Task> task;
            size_t dependencies;
        };

        class PoolThread:public Thread {
        private:
            friend class ThreadPoolExecutor;

            ThreadPoolExecutor& executor;
            Waitable waitable;

        public:
            PoolThread(ThreadPoolExecutor& executor):executor(executor) {}

            void* tag = nullptr;
            SharedPointer<Task> task;

            void execute(SharedPointer<Task> task) {
                this->task = task;
                tag = task->Tag;
                waitable.notify();
            }

            virtual void run() override;
        };

        LinkedList<LinkedList<SharedPointer<Task>>> tasks;
        LinkedList<PoolThread*> busyThreads, waitingThreads, threads;
        CriticalSection section;

        // returns max depth
        size_t flattenTaskGraph(SharedPointer<Task>& task, List<TaskExecution>& taskList);

        void onTaskFinished(PoolThread& thread, SharedPointer<Task>& justFinished);

        inline bool isTagUsed(void* tag) {
            for (PoolThread* t : busyThreads) {
                if (t->tag == tag)
                    return true;
            }
            return false;
        }

        SharedPointer<Task> findNextTask();

        bool queueNextTask();

    public:
        ThreadPoolExecutor();

        ThreadPoolExecutor(uint8_t poolSize);

        ~ThreadPoolExecutor();

        void post(SharedPointer<Task> task);

        inline uint8_t getPoolSize() const {
            return (uint8_t)threads.Size;
        }

        __declspec(property(get = getPoolSize)) uint8_t PoolSize;
    };
}