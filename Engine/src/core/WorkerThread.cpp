#include "WorkerThread.h"

namespace Ghurund {
    void WorkerThread::post(Task * task, long delayMs) {
        section.enter();
        timer.tick();
        task->addReference();
        time_t time = (time_t)(timer.RunTime*1000);
        task->time = time + delayMs;
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
                timer.tick();
                time_t time = (time_t)(timer.RunTime*1000);
                Task *task = queue.get(0);
                if(task->time>time) {
                    section.leave();
                    wait((DWORD)(task->time-time));
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