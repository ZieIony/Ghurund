#include "graphics/entity/Camera.h"

#include "../Float3.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Camera *Camera_new() {
    return new Camera();
}

extern "C" __declspec(dllexport) void Camera_initParameters(Camera *_this, ParameterManager *manager) {
    _this->initParameters(*manager);
}

extern "C" __declspec(dllexport) Float3 Camera_getTarget(Camera *_this) {
    return convertFloat3(_this->getTarget());
}

extern "C" __declspec(dllexport) Float3 Camera_getDirection(Camera *_this) {
    return convertFloat3(_this->getDirection());
}

extern "C" __declspec(dllexport) Float3 Camera_getUp(Camera *_this) {
    return convertFloat3(_this->getUp());
}

extern "C" __declspec(dllexport) void Camera_setScreenSize(Camera *_this, unsigned int width, unsigned int height) {
    _this->setScreenSize(width, height);
}

extern "C" __declspec(dllexport) void Camera_setPositionTargetUp(Camera *_this, Float3 pos, Float3 target, Float3 up) {
    _this->setPositionTargetUp(convertFloat3(pos), convertFloat3(target), convertFloat3(up));
}
extern "C" __declspec(dllexport) void Camera_setPositionDirectionDistanceUp(Camera *_this, Float3 pos, Float3 dir, float dist, Float3 up) {
    _this->setPositionDirectionDistanceUp(convertFloat3(pos), convertFloat3(dir), dist, convertFloat3(up));
}

extern "C" __declspec(dllexport) void Camera_setRotation(Camera *_this, float yaw, float pitch, float roll) {
    _this->setRotation(yaw, pitch, roll);
}

extern "C" __declspec(dllexport) void Camera_setOrbit(Camera *_this, float yaw, float pitch, float roll) {
    _this->setOrbit(yaw, pitch, roll);
}

extern "C" __declspec(dllexport) void Camera_rotate(Camera *_this, float yaw, float pitch, float roll) {
    _this->rotate(yaw, pitch, roll);
}

extern "C" __declspec(dllexport) void Camera_orbit(Camera *_this, float yaw, float pitch, float roll) {
    _this->orbit(yaw, pitch, roll);
}

extern "C" __declspec(dllexport) void Camera_pan(Camera *_this, float x, float y) {
    _this->pan(x, y);
}

extern "C" __declspec(dllexport) void Camera_zoom(Camera *_this, float z) {
    _this->zoom(z);
}

extern "C" __declspec(dllexport) const Array<ResourceFormat*> *Camera_getFormats() {
    return &Camera::getFormats();
}

extern "C" __declspec(dllexport) BOOL Camera_getPerspective(Camera *_this) {
    return _this->getPerspective();
}

extern "C" __declspec(dllexport) void Camera_setPerspective(Camera *_this, BOOL pers) {
    _this->setPerspective(pers);
}
