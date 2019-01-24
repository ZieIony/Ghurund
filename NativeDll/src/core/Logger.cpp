#include "../../stdafx.h"
#include "core/Logger.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) void Logger_init(void(__stdcall *onLogged)(const tchar *log)) {
    Logger::init(LogOutput::CUSTOM_CALLBACK, nullptr, onLogged);
}

extern "C" __declspec(dllexport) void Logger_log(const tchar *log) {
    Logger::log(log);
}
