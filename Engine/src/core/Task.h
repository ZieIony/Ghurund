#pragma once

#include "Thread.h"
#include "Pointer.h"
#include "collection/String.h"
#include "collection/Array.h"

namespace Ghurund {
    class Task:public Pointer {
    private:
        friend class WorkerThread;

        unsigned int id;
        String name;
        std::function<Status()> function;
        Status result = Status::UNKNOWN;
        time_t time;

    public:

        Task(const String &name, std::function<Status()> function) {
            static unsigned int currentId = 0;

            id = currentId++;
            this->name = name;
            this->function = function;
        }

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
}