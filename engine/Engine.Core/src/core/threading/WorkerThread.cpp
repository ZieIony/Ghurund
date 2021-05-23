#include "ghcpch.h"
#include "WorkerThread.h"

#include "core/logging/Logger.h"

namespace Ghurund {
    void WorkerThread::run() {
        running.test_and_set();
        while (true) {
            waitable.wait();
            busy.test_and_set();
            while (true) {
                if (!running.test())
                    return;
                section.enter();
                if (queue.Empty)
                    break;
                SharedPointer<Task> task = queue.front();
                queue.remove();
                section.leave();
                Logger::print(LogType::INFO, _T("executing task '{}' on thread '{}'\n"), task->Name, Name);
                task->run();
                Logger::print(LogType::INFO, _T("finished task '{}' on thread '{}'\n"), task->Name, Name);
            }
            busy.clear();
        }
    }
}
