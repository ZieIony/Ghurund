#include "graphics/Camera.h"
#include "../Float3.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Camera *Camera_new() {
    return new Camera();
}

extern "C" __declspec(dllexport) void Camera_initParameters(Camera *_this, ParameterManager *manager) {
    _this->initParameters(*manager);
}

extern "C" __declspec(dllexport) void Camera_setScreenSize(Camera *_this, unsigned int width, unsigned int height) {
    _this->setScreenSize(width, height);
}

extern "C" __declspec(dllexport) void Camera_setPositionTargetUp(Camera *_this, Float3 pos, Float3 target, Float3 up) {
    _this->setPositionTargetUp(convertFloat3(pos), convertFloat3(target), convertFloat3(up));
}

extern "C" __declspec(dllexport) void Camera_setPositionDirectionUp(Camera *_this, Float3 pos, Float3 dir, Float3 up) {
    _this->setPositionDirectionUp(convertFloat3(pos), convertFloat3(dir), convertFloat3(up));
}

extern "C" __declspec(dllexport) void Camera_rotate(Camera *_this, float yaw, float pitch, float roll) {
    _this->rotate(yaw, pitch, roll);
}

extern "C" __declspec(dllexport) void Camera_orbit(Camera *_this, float yaw, float pitch, float roll) {
    _this->orbit(yaw, pitch, roll);
}

extern "C" __declspec(dllexport) void Camera_pan(Camera *_this, Float3 pan) {
    _this->pan(convertFloat3(pan));
}

extern "C" __declspec(dllexport) void Camera_setRotation(Camera *_this, float yaw, float pitch, float roll) {
    _this->setRotation(yaw, pitch, roll);
}

extern "C" __declspec(dllexport) void Camera_setOrbit(Camera *_this, float yaw, float pitch, float roll) {
    _this->setOrbit(yaw, pitch, roll);
}
