#pragma once

#include "Thread.h"
#include "core/collection/Array.h"
#include "core/Id.h"
#include "core/NamedObject.h"
#include "core/Pointer.h"
#include "Status.h"

namespace Ghurund {
    class Task:public Pointer, public NamedObject, public IdObject<Task> {
    private:
        friend class WorkerThread;

        std::function<Status()> function;
        Status result = Status::UNKNOWN;
        time_t time;

        static const Ghurund::Type& GET_TYPE();

    public:
        Task(std::function<Status()> function) {
            this->function = function;
        }

        Task(const WString& name, std::function<Status()> function) {
            this->Name = name;
            this->function = function;
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
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