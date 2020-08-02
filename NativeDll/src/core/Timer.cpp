#include "application/Timer.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Timer* Timer_new() {
    return new Timer();
}

extern "C" __declspec(dllexport) float Timer_getTime(Timer* _this) {
    return _this->getTime();
}

extern "C" __declspec(dllexport) void Timer_setPaused(Timer* _this, bool p) {
    _this->setPaused(p);
}

extern "C" __declspec(dllexport) bool Timer_isPaused(Timer* _this) {
    return _this->isPaused();
}
