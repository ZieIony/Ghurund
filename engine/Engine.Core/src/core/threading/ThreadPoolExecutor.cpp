#include "ghcpch.h"
#include "ThreadPoolExecutor.h"

namespace Ghurund::Core {

    void ThreadPoolExecutor::PoolThread::run() {
        while (true) {
            waitable.wait();
            auto text = std::format(_T("executing task '{}' on thread '{}'\n"), task->name, name);
            Logger::print(LogType::INFO, text.c_str());
            task->run();
            tag = nullptr;
            auto text2 = std::format(_T("finished task '{}' on thread '{}'\n"), task->name, name);
            Logger::print(LogType::INFO, text2.c_str());
            executor.section.enter();
            executor.onTaskFinished(*this, task);
            while (executor.queueNextTask());
            executor.section.leave();
        }
    }

    // returns max depth
    size_t ThreadPoolExecutor::flattenTaskGraph(SharedPointer2<Task>& task, List<TaskExecution>& taskList) {
        size_t depth = 0;
        for (SharedPointer2<Task>& t : task->Dependencies)
            depth = std::max(depth, flattenTaskGraph(t, taskList) + 1);
        taskList.add({ task, depth });
        return depth;
    }

    void ThreadPoolExecutor::onTaskFinished(PoolThread& thread, SharedPointer2<Task>& justFinished) {
        busyThreads.remove(&thread);
        waitingThreads.add(&thread);
        for (size_t i = 0; i < tasks.Size; i++) {
            LinkedList<SharedPointer2<Task>>& taskList = tasks[i];
            for (size_t j = 0; j < taskList.Size;j++) {
                if (taskList[j] == justFinished) {
                    if (justFinished->ExecutionStatus == ExecutionStatus::SUCCEEDED) {
                        taskList.removeAt(j);
                    } else {
                        for (SharedPointer2<Task>& t2 : taskList)
                            t2->skip();
                        tasks.removeAt(i);
                    }
                    return;
                }
            }
        }
    }

    SharedPointer2<Task> ThreadPoolExecutor::findNextTask() {
        for (LinkedList<SharedPointer2<Task>>& taskList : tasks) {
            SharedPointer2<Task>& t = taskList.front();
            if (t->Tag && isTagUsed(t->Tag))
                continue;
            if (taskList.Empty)
                tasks.remove(taskList);
            return t;
        }
        return {};
    }

    bool ThreadPoolExecutor::queueNextTask() {
        if (waitingThreads.Empty)
            return false;
        SharedPointer2<Task> task = findNextTask();
        if (&task == nullptr)
            return false;
        PoolThread* thread = waitingThreads[0];
        waitingThreads.removeFront();
        busyThreads.add(thread);
        thread->execute(task);
        return true;
    }

    ThreadPoolExecutor::ThreadPoolExecutor():ThreadPoolExecutor((uint8_t)std::max(64, SystemInfo::getProcessorInfo().logicalProcessors - 1)) {}

    ThreadPoolExecutor::ThreadPoolExecutor(uint8_t poolSize) {
        for (uint8_t i = 0; i < poolSize; i++) {
            auto thread = ghnew PoolThread(*this);
            thread->name = std::format("{}", i).c_str();
            threads.add(thread);
            waitingThreads.add(thread);
            thread->start();
        }
    }

    ThreadPoolExecutor::~ThreadPoolExecutor() {
        section.enter();
        tasks.clear();
        section.leave();
        for (size_t i = 0; i < threads.Size; i++)
            delete threads[i];
    }

    void ThreadPoolExecutor::post(SharedPointer2<Task> task) {
        List<TaskExecution> taskList;
        flattenTaskGraph(task, taskList);
        std::sort(taskList.begin(), taskList.end(), [](TaskExecution& a, TaskExecution& b)->bool {
            return a.dependencies < b.dependencies;
        });
        section.enter();
        LinkedList<SharedPointer2<Task>> taskLinkedList;
        for(auto& t:taskList)
            taskLinkedList.add(t.task);
        tasks.add(taskLinkedList);
        queueNextTask();
        section.leave();
    }

}