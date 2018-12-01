#include "game/parameter/ParameterManager.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) ParameterManager *ParameterManager_new() {
    return new ParameterManager();
}

extern "C" __declspec(dllexport) size_t ParameterManager_getParameterCount(ParameterManager *_this) {
    return _this->getParameterCount();
}

extern "C" __declspec(dllexport) Parameter *ParameterManager_get(ParameterManager *_this, size_t index) {
    return _this->get(index);
}
