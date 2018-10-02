#pragma once

#include "Thread.h"

namespace Ghurund {
    class Task:public Pointer {
    private:
        friend class WorkerThread;

        Task(const String &name, std::function<Status()> function) {
            static unsigned int currentId = 0;

            id = currentId++;
            this->name = name;
            this->function = function;
        }

        unsigned int id;
        String name;
        std::function<Status()> function;
        Status result = Status::UNKNOWN;

    public:
        unsigned int getId() const {
            return id;
        }

        __declspec(property(get = getId)) unsigned int Id;

        const String &getName() const {
            return name;
        }

        __declspec(property(get = getName)) String &Name;

        virtual const Ghurund::Type &getType() const override {
            static const Ghurund::Type &TASK = Ghurund::Type(nullptr, _T("task"));

            return TASK;
        }

        void run() {
            result = function();
        }

        Status getResult() {
            return result;
        }
    };

    class WorkerThread:public Thread {
    private:
        std::deque<Task*> queue;
        CriticalSection section;

    protected:
        virtual void wakeUp() {
            notify();
        }

    public:

        void post(const String &name, std::function<Status()> function) {
            section.enter();
            Task *task = ghnew Task(name, function);
            queue.push_back(task);
            section.leave();
            notify();
        }

        void remove(Task *task) {
            section.enter();
            for(auto it = queue.begin(); it!=queue.end(); ++it) {
                if((*it)->id==task->id) {
                    queue.erase(it);
                    break;
                }
            }
            section.leave();
        }

        /**
        * Gets a copy of tasks queued for execution at the time of the getTasks() call.
        */
        Array<Task*> *getTasks() {
            section.enter();
            Array<Task*> *tasks = new Array<Task*>(queue.size());
            size_t i = 0;
            for(auto it = queue.begin(); it!=queue.end(); ++it) {
                Task *task = *it;
                task->addReference();
                tasks->set(i++, task);
            }
            section.leave();
            return tasks;
        }

        __declspec(property(get = getTasks)) Array<Task*> *Tasks;

        void run() {
            while(!isFinishing()) {
                wait();
                while(true) {
                    section.enter();
                    if(queue.empty()) {
                        section.leave();
                        break;
                    }
                    Task *task = queue.front();
                    queue.pop_front();
                    section.leave();
                    task->run();
                    task->release();
                }
            }
        }
    };
}