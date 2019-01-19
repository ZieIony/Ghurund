#include "game/entity/Entity.h"
#include "../Float3.h"
#include "game/entity/TransformedEntity.h"

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

extern "C" __declspec(dllexport) wchar_t *Entity_getName(Entity *_this) {
    return copyStr(_this->getName().getData());
}

extern "C" __declspec(dllexport) void Entity_setName(Entity *_this, const wchar_t *name) {
    _this->setName(name);
}

extern "C" __declspec(dllexport) const Float3 TransformedEntity_getPosition(TransformedEntity *_this) {
    return convertFloat3(_this->getPosition());
}

extern "C" __declspec(dllexport) void TransformedEntity_setPosition(TransformedEntity *_this, XMFLOAT3 position) {
    _this->setPosition(position);
}

extern "C" __declspec(dllexport) const Float3 TransformedEntity_getRotation(TransformedEntity *_this) {
    return convertFloat3(_this->getRotation());
}

extern "C" __declspec(dllexport) void TransformedEntity_setRotation(TransformedEntity *_this, XMFLOAT3 rotation) {
    _this->setRotation(rotation);
}

extern "C" __declspec(dllexport) const Float3 TransformedEntity_getScale(TransformedEntity *_this) {
    return convertFloat3(_this->getScale());
}

extern "C" __declspec(dllexport) void TransformedEntity_setScale(TransformedEntity *_this, XMFLOAT3 scale) {
    _this->setScale(scale);
}

extern "C" __declspec(dllexport) Entity *TransformedEntity_getEntity(TransformedEntity *_this) {
    return _this->getEntity();
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

extern "C" __declspec(dllexport) const Array<ResourceFormat*> *TransformedEntity_getFormats() {
    return &TransformedEntity::getFormats();
}
