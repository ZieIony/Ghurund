#pragma once

#include "Status.h"
#include "core/collection/Array.h"
#include "core/Id.h"
#include "core/NamedObject.h"
#include "core/SharedPointer.h"
#include "core/Event.h"

#include <functional>

namespace Ghurund {
    enum class ExecutionStatus {
        NOT_STARTED, IN_PROGRESS, SUCCEEDED, SKIPPED, FAILED
    };

    class Task:public Pointer, public NamedObject {
    private:
        std::function<Status()> function;
        List<SharedPointer<Task>> dependencies;
        void* tag = nullptr;
        ExecutionStatus executionStatus = ExecutionStatus::NOT_STARTED;
        Event<Task, ExecutionStatus> statusChanged = *this;

        static const Ghurund::Type& GET_TYPE();

    public:
        Task(std::function<Status()> function):function(function) {}

        Task(const WString& name, std::function<Status()> function):function(function) {
            this->Name = name;
            this->function = function;
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        inline void run() {
            executionStatus = ExecutionStatus::IN_PROGRESS;
            statusChanged(executionStatus);
            Status result = function();
            executionStatus = result == Status::OK ? ExecutionStatus::SUCCEEDED : ExecutionStatus::FAILED;
            statusChanged(executionStatus);
        }

        inline bool skip() {
            if (executionStatus != ExecutionStatus::NOT_STARTED)
                return false;
            executionStatus = ExecutionStatus::SKIPPED;
            statusChanged(executionStatus);
            return true;
        }

        inline bool isReady() {
            bool ready = true;
            for (auto& dep : dependencies)
                ready &= dep->ExecutionStatus == ExecutionStatus::SUCCEEDED;
            return ready;
        }

        __declspec(property(get = isReady)) bool Ready;

        inline ExecutionStatus getExecutionStatus() const {
            return executionStatus;
        }

        inline void setExecutionStatus(ExecutionStatus status) {
            this->executionStatus = status;
        }

        __declspec(property(get = getExecutionStatus, put = setExecutionStatus)) ExecutionStatus ExecutionStatus;

        inline List<SharedPointer<Task>>& getDependencies() {
            return dependencies;
        }

        __declspec(property(get = getDependencies)) List<SharedPointer<Task>>& Dependencies;

        inline void* getTag() {
            return tag;
        }

        inline void setTag(void* tag) {
            this->tag = tag;
        }

        __declspec(property(get = getTag, put = setTag)) void* Tag;

        inline Event<Task, Ghurund::ExecutionStatus>& getOnExecutionStatusChanged() {
            return statusChanged;
        }

        __declspec(property(get = getOnExecutionStatusChanged)) Event<Task, Ghurund::ExecutionStatus>& OnExecutionStatusChanged;
    };

    class TaskGroup {
    private:
        List<SharedPointer<Task>> tasks;
        ExecutionStatus executionStatus = ExecutionStatus::NOT_STARTED;
        float progress = 0.0f;

    public:
        TaskGroup() {}

        TaskGroup(SharedPointer<Task> task) {
            tasks.add(task);
        }

        inline ExecutionStatus getExecutionStatus() const {
            return executionStatus;
        }

        __declspec(property(get = getExecutionStatus)) ExecutionStatus ExecutionStatus;

        inline float getProgress() const {
            return progress;
        }

        __declspec(property(get = getProgress)) float Progress;

        List<SharedPointer<Task>>& getTasks() {
            return tasks;
        }

        __declspec(property(get = getTasks)) List<SharedPointer<Task>>& Tasks;

        inline SharedPointer<Task> startTask() {

        }
    };
}