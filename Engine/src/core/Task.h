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

		static const Ghurund::Type& TYPE;

        virtual const Ghurund::Type &getType() const override {
            return TYPE;
        }

        void run() {
            result = function();
        }

        Status getResult() const {
            return result;
        }

		__declspec(property(get = getResult)) Status Result;
    };
}