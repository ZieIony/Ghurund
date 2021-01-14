#pragma once

#include "Task.h"
//#include "application/Timer.h"
#include "core/Pointer.h"
#include "core/collection/Array.h"
#include "core/collection/List.h"
#include "core/string/WString.h"

namespace Ghurund {
    class WorkerThread:public Thread {
    private:
        List<Task*> queue;
        CriticalSection section;
        //Timer timer;

    protected:
        virtual void wakeUp() {
            notify();
        }

    public:

        void post(Task *task, long delayMs = 0);

        void remove(const WString &taskName);

        void remove(Task *task);

        /**
        * Gets a copy of tasks queued for execution at the time of the getTasks() call.
        */
        Array<Task*> *getTasks();

        __declspec(property(get = getTasks)) Array<Task*> *Tasks;

        void run();
    };
}