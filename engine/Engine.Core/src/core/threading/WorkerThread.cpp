#include "ghcpch.h"
#include "WorkerThread.h"

#include "core/logging/Logger.h"

namespace Ghurund::Core {
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
        }
    }
}
