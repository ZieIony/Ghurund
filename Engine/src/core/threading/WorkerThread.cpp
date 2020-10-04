#include "WorkerThread.h"

namespace Ghurund {
    void WorkerThread::post(Task* task, long delayMs) {
        section.enter();
        timer.tick();
        task->addReference();
        time_t time = (time_t)(timer.Time * 1000);
        task->time = time + delayMs;
        for (size_t i = 0; i < queue.Size; i++) {
            Task* t = queue[i];
            if (t->time < task->time) {
                queue.insert(i, task);
                section.leave();
                notify();
                return;
            }
        }
        queue.add(task);
        section.leave();
        notify();
    }

    void WorkerThread::remove(const String& taskName) {
        section.enter();
        for (size_t i = 0; i < queue.Size; i++) {
            if (queue[i]->Name == taskName) {
                Task* task = queue[i];
                queue.removeAt(i);
                task->release();
                break;
            }
        }
        section.leave();
    }

    void WorkerThread::remove(Task* task) {
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
        Array<Task*>* tasks = new Array<Task*>(queue.Size);
        size_t i = 0;
        for (size_t i = 0; i < queue.Size; i++) {
            Task* task = queue[i];
            task->addReference();
            tasks->set(i, task);
        }
        section.leave();
        return tasks;
    }

    void WorkerThread::run() {
        while (!isFinishing()) {
            wait();
            while (true) {
                section.enter();
                if (queue.Empty) {
                    section.leave();
                    break;
                }
                timer.tick();
                time_t time = (time_t)(timer.Time * 1000);
                Task* task = queue.get(0);
                if (task->time > time) {
                    section.leave();
                    wait((DWORD)(task->time - time));
                } else {
                    queue.removeAt(0);
                    section.leave();
                    task->run();
                    task->release();
                }
            }
        }
    }
}