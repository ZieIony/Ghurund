#include "core/SystemInfo.h"
#include "core/object/IntrusivePointer.h"
#include "core/logging/Logger.h"
#include "engine/directx/Graphics.h"
#include "Ghurund.Engine.h"

using namespace Ghurund::Core;
using namespace Ghurund::Engine::DirectX;

const uint32_t KB = 1024;
const uint32_t MB = 1024 * 1024;

int main() {
	Logger::init(std::unique_ptr<LogOutput>(ghnew StandardConsoleLogOutput()));
	auto processor = SystemInfo::getProcessorInfo();
	auto textCpu = std::format(
		_T("processor\narchitecture: {}, cores: {}, logical: {}\n\n"),
		processor.architecture, processor.cores, processor.logicalProcessors
	);
	Logger::print(LogType::INFO, textCpu.c_str());
	auto memory = SystemInfo::getMemoryInfo();
	auto textMem = std::format(
		_T("memory\ntotal: {}MB ({}B), working set: {}MB ({}B)\n\n"),
		memory.totalKb / KB, memory.totalKb,
		memory.workingSet / MB, memory.workingSet
	);
	Logger::print(LogType::INFO, textMem.c_str());

	auto graphics = makeIntrusive<Graphics>();
	graphics->init();
	for (auto& adapter : graphics->Adapters) {
		auto vmem = adapter->DedicatedVideoMemory;
		auto sharedmem = adapter->SharedSystemMemory;
		auto textAdapter = std::format(
			_T("video adapter: {}\ndedicated video memory: {}MB ({}b), shared memory: {}MB ({}b)\n"),
			adapter->Name, vmem / MB,
			vmem, sharedmem / MB, sharedmem
		);
		Logger::print(LogType::INFO, textAdapter.c_str());
		for (auto& output : adapter->Outputs) {
			Logger::print(LogType::INFO, std::format(_T("  output: {}\n"), output->Name).c_str());
			for (auto& dm : output->DisplayModes)
				Logger::print(LogType::INFO, std::format(_T("    {}x{} {}Hz\n"), dm->Width, dm->Height, dm->RefreshRate).c_str());
		}
		Logger::print(LogType::INFO, _T("\n"));
	}
}
