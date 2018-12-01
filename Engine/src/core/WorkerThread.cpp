#include "WorkerThread.h"
#include <time.h>

namespace Ghurund {
    void WorkerThread::post(Task * task, long delayMs) {
        section.enter();
        time_t timer;
        time(&timer);
        task->addReference();
        task->time = timer + delayMs;
        queue.add(task);
        section.leave();
        notify();
    }

    void WorkerThread::remove(Task *task) {
        section.enter();
        queue.remove(task);
        task->release();
        section.leave();
    }

    /**
    * Gets a copy of tasks queued for execution at the time of the getTasks() call.
    */
    Array<Task*>* WorkerThread::getTasks() {
        section.enter();
        Array<Task*> *tasks = new Array<Task*>(queue.Size);
        size_t i = 0;
        for(size_t i = 0; i<queue.Size;i++) {
            Task *task = queue[i];
            task->addReference();
            tasks->set(i, task);
        }
        section.leave();
        return tasks;
    }

    void WorkerThread::run() {
        while(!isFinishing()) {
            wait();
            while(true) {
                section.enter();
                if(queue.Empty) {
                    section.leave();
                    break;
                }
                time_t timer;
                time(&timer);
                Task *task = queue.get(0);
                if(task->time>timer) {
                    section.leave();
                    wait((DWORD)(timer-task->time));
                } else {
                    queue.removeAtKeepOrder(0);
                    section.leave();
                    task->run();
                    task->release();
                }
            }
        }
    }
}