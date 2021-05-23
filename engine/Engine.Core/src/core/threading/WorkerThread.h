#pragma once

#include "ConcurrentTaskQueue.h"
#include "Thread.h"
#include "Task.h"
#include "core/Pointer.h"
#include "Waitable.h"
#include "core/collection/List.h"
#include "core/string/String.h"

namespace Ghurund {
    class WorkerThread:public Thread {
    private:
        Queue<SharedPointer<Task>> queue;
        mutable CriticalSection section;
        Waitable waitable;
        std::atomic_flag busy;
        std::atomic_flag running;

    public:
        virtual ~WorkerThread() {
            if (running.test())
                finish();
        }

        virtual void finish() override {
            running.test_and_set();
            waitable.notify();
            __super::finish();
        }

        inline void post(SharedPointer<Task> task) {
            section.enter();
            queue.add(task);
            waitable.notify();
            section.leave();
        }

        inline Queue<SharedPointer<Task>> getTasks() const {
            section.enter();
            Queue<SharedPointer<Task>> copy = queue;
            section.leave();
            return queue;
        }

        __declspec(property(get = getTasks)) Queue<SharedPointer<Task>> Tasks;

        virtual void run() override;

        inline bool isRunning() const {
            return running.test();
        }

        __declspec(property(get = isRunning)) bool Running;

        inline bool isBusy() const {
            return busy.test();
        }

        __declspec(property(get = isBusy)) bool Busy;
    };
}