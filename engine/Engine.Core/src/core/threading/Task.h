#pragma once

#include "Status.h"
#include "core/collection/Array.h"
#include "core/Id.h"
#include "core/SharedPointer2.h"
#include "core/Event.h"

#include <functional>

namespace Ghurund::Core {
    enum class ExecutionStatus {
        NOT_STARTED, IN_PROGRESS, SUCCEEDED, SKIPPED, FAILED
    };

    class Task {
    private:
        std::function<Status()> function;
        List<SharedPointer2<Task>> dependencies;
        void* tag = nullptr;
        ExecutionStatus executionStatus = ExecutionStatus::NOT_STARTED;
        Event<Task, ExecutionStatus> statusChanged = *this;

    public:
        WString name;
     
        Task(std::function<Status()> function):function(function) {}

        Task(const WString& name, std::function<Status()> function):function(function) {
            this->name = name;
            this->function = function;
        }

        inline void run() {
            executionStatus = ExecutionStatus::IN_PROGRESS;
            statusChanged(executionStatus);
            try {
                function();
                executionStatus = ExecutionStatus::SUCCEEDED;
            } catch (...) {
                executionStatus = ExecutionStatus::FAILED;
            }
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

        inline List<SharedPointer2<Task>>& getDependencies() {
            return dependencies;
        }

        __declspec(property(get = getDependencies)) List<SharedPointer2<Task>>& Dependencies;

        inline void* getTag() {
            return tag;
        }

        inline void setTag(void* tag) {
            this->tag = tag;
        }

        __declspec(property(get = getTag, put = setTag)) void* Tag;

        inline Event<Task, Ghurund::Core::ExecutionStatus>& getOnExecutionStatusChanged() {
            return statusChanged;
        }

        __declspec(property(get = getOnExecutionStatusChanged)) Event<Task, Ghurund::Core::ExecutionStatus>& OnExecutionStatusChanged;
    };

    class TaskGroup {
    private:
        List<SharedPointer2<Task>> tasks;
        ExecutionStatus executionStatus = ExecutionStatus::NOT_STARTED;
        float progress = 0.0f;

    public:
        TaskGroup() {}

        TaskGroup(SharedPointer2<Task> task) {
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

        List<SharedPointer2<Task>>& getTasks() {
            return tasks;
        }

        __declspec(property(get = getTasks)) List<SharedPointer2<Task>>& Tasks;

        inline SharedPointer2<Task> startTask() {

        }
    };
}