#include "ghcpch.h"
#include "WorkerThread.h"

#include "core/logging/Logger.h"

namespace Ghurund::Core {
    void WorkerThread::run() {
        running.test_and_set();
        runningChanged(true);
        while (true) {
            waitable.wait();
            busy.test_and_set();
            busyChanged(true);
            while (true) {
                if (finishing.test()) {
                    running.clear();
                    runningChanged(false);
                    return;
                }
                SharedPointer<Task> task;
                {
                    SectionLock lock(section);
                    if (queue.Empty)
                        break;
                    task = queue.front();
                    queue.remove();
                }
#ifdef _DEBUG
                auto text = std::format(_T("executing task '{}' on thread '{}'\n"), task->Name, Name);
                Logger::print(LogType::INFO, text.c_str());
#endif
                task->run();
#ifdef _DEBUG
                auto text2 = std::format(_T("finished task '{}' on thread '{}'\n"), task->Name, Name);
                Logger::print(LogType::INFO, text2.c_str());
#endif
            }
            busy.clear();
            busyChanged(false);
        }
    }
}
