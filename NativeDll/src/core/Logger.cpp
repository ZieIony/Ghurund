#include "../../stdafx.h"
#include "core/Logger.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) void Logger_init(void(__stdcall *onLogged)(const tchar *log)) {
    Logger::init(LogOutput::CUSTOM_CALLBACK, nullptr, onLogged);
}

extern "C" __declspec(dllexport) void Logger_log(LogTypeEnum type, const tchar *log) {
    if (type == LogTypeEnum::INFO) {
        Logger::log(LogType::INFO, log);
    } else if (type == LogTypeEnum::WARNING) {
        Logger::log(LogType::WARNING, log);
    } else if (type == LogTypeEnum::ERR0R) {
        Logger::log(LogType::ERR0R, log);
    }
}
