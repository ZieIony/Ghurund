#include "core/SystemInfo.h"
#include "core/logging/Logger.h"
#include <core/threading/ThreadPoolExecutor.h>

using namespace Ghurund::Core;

int main() {
    Logger::init(std::unique_ptr<LogOutput>(ghnew StandardConsoleLogOutput()));
    auto processor = SystemInfo::getProcessorInfo();
    Logger::print(LogType::INFO, _T("\nprocessor\ncores: {}, logical: {}\n"), processor.cores, processor.logicalProcessors);
    auto memory = SystemInfo::getMemoryInfo();
    Logger::print(LogType::INFO, _T("\nmemory\ntotal: {}, working set: {}\n"), memory.total, memory.workingSet);

    Logger::print(LogType::INFO, _T("\n\n"));

    ThreadPoolExecutor executor(4);
    for (size_t i = 0; i < 10; i++) {
        SharedPointer<Task> readTask = ghnew Task(L"read", []() {
            Sleep(500);
            return Status::OK;
        });
        SharedPointer<Task> decodeTask = ghnew Task(L"decode", []() {
            Sleep(500);
            return Status::OK;
        });
        decodeTask->Dependencies.add(readTask);
        executor.post(decodeTask);
    }

    Sleep(5000);
}
