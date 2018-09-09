#include "graphics/Camera.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Camera *Camera_new() {
    return new Camera();
}

extern "C" __declspec(dllexport) void Camera_initParameters(Camera *_this, ParameterManager *manager) {
    _this->initParameters(*manager);
}
