#pragma once

#include "Task.h"
#include "Pointer.h"
#include "collection/String.h"
#include "collection/Array.h"
#include "collection/List.h"
#include "Timer.h"

namespace Ghurund {
    class WorkerThread:public Thread {
    private:
        List<Task*> queue;
        CriticalSection section;
        Timer timer;

    protected:
        virtual void wakeUp() {
            notify();
        }

    public:

        void post(Task *task, long delayMs = 0);

        void remove(const String &taskName);

        void remove(Task *task);

        /**
        * Gets a copy of tasks queued for execution at the time of the getTasks() call.
        */
        Array<Task*> *getTasks();

        __declspec(property(get = getTasks)) Array<Task*> *Tasks;

        void run();
    };
}