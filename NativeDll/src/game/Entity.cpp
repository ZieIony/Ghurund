#include "game/Entity.h"
#include "../Float3.h"

using namespace Ghurund;

extern "C" __declspec(dllexport) Array<Parameter*> *ParameterProvider_getParameters(ParameterProvider *_this) {
    return &_this->getParameters();
}

extern "C" __declspec(dllexport) void ParameterProvider_initParameters(ParameterProvider *_this, ParameterManager *manager) {
    _this->initParameters(*manager);
}

extern "C" __declspec(dllexport) void ParameterProvider_updateParameters(ParameterProvider *_this) {
    _this->updateParameters();
}

extern "C" __declspec(dllexport) const Type *Entity_getType(Entity *_this) {
    return &(_this->Type);
}

extern "C" __declspec(dllexport) tchar *Entity_getName(Entity *_this) {
    return copyStr(_this->getName().getData());
}

extern "C" __declspec(dllexport) void Entity_setName(Entity *_this, const tchar *fileName) {
    _this->setName(fileName);
}

extern "C" __declspec(dllexport) const Float3 TransformedObject_getPosition(TransformedObject *_this) {
    return convertFloat3(_this->getPosition());
}

extern "C" __declspec(dllexport) void TransformedObject_setPosition(TransformedObject *_this, XMFLOAT3 position) {
    _this->setPosition(position);
}

extern "C" __declspec(dllexport) const Float3 TransformedObject_getRotation(TransformedObject *_this) {
    return convertFloat3(_this->getRotation());
}

extern "C" __declspec(dllexport) void TransformedObject_setRotation(TransformedObject *_this, XMFLOAT3 rotation) {
    _this->setRotation(rotation);
}

extern "C" __declspec(dllexport) const Float3 TransformedObject_getScale(TransformedObject *_this) {
    return convertFloat3(_this->getScale());
}

extern "C" __declspec(dllexport) void TransformedObject_setScale(TransformedObject *_this, XMFLOAT3 scale) {
    _this->setScale(scale);
}

extern "C" __declspec(dllexport) Array<Parameter*> *Entity_getParameters(Entity *_this) {
    return &_this->getParameters();
}

extern "C" __declspec(dllexport) void Entity_initParameters(Entity *_this, ParameterManager *manager) {
    _this->initParameters(*manager);
}

extern "C" __declspec(dllexport) void Entity_updateParameters(Entity *_this) {
    _this->updateParameters();
}
