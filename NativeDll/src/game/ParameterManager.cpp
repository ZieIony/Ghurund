#include "game/parameter/ParameterManager.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) ParameterManager *ParameterManager_new() {
    return new ParameterManager();
}

extern "C" __declspec(dllexport) PointerList<Parameter*> *ParameterManager_getParameters(ParameterManager *_this) {
    return &_this->getParameters();
}

extern "C" __declspec(dllexport) void ParameterManager_initDefaultTextures(ParameterManager *_this, ResourceContext *context) {
    _this->initDefaultTextures(*context);
}
