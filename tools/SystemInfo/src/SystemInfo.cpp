#include "core/SystemInfo.h"
#include "core/logging/Logger.h"
#include <core/threading/ThreadPoolExecutor.h>

using namespace Ghurund::Core;

int main() {
	Logger::init(std::unique_ptr<LogOutput>(ghnew StandardConsoleLogOutput()));
	auto processor = SystemInfo::getProcessorInfo();
	Logger::print(LogType::INFO, std::format(_T("\nprocessor\ncores: {}, logical: {}\n"), processor.cores, processor.logicalProcessors).c_str());
	auto memory = SystemInfo::getMemoryInfo();
	Logger::print(LogType::INFO, std::format(_T("\nmemory\ntotal: {}, working set: {}\n"), memory.total, memory.workingSet).c_str());
}
