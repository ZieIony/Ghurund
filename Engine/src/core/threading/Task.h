#pragma once

#include "Thread.h"
#include "core/string/String.h"
#include "core/collection/Array.h"
#include "core/Id.h"
#include "core/NamedObject.h"
#include "core/Pointer.h"

namespace Ghurund {
    class Task:public Pointer, public NamedObject<String>, public IdObject<Task> {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Task);
        
        friend class WorkerThread;

        std::function<Status()> function;
        Status result = Status::UNKNOWN;
        time_t time;

    public:
        Task(const String &name, std::function<Status()> function) {
            this->Name = name;
            this->function = function;
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<Task>(NAMESPACE_NAME, CLASS_NAME).withSupertype(Pointer::TYPE);

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